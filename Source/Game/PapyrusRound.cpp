#include "stdafx.h"
#include "PapyrusRound.h"

void PapyrusRound::SetAllData(int selection)
{
    allData.clear();
    allData.shrink_to_fit();
    enemyBarrage.clear();
    enemyBarrage.shrink_to_fit();

    if(selection!=-99)
    {
        currentRound=selection;
    }

    if(currentRound==-1)
    {
        HandleJsonData("RoundXData","PapyrusRounds");    
    }
    else
    {
        HandleJsonData("Round"+to_string(currentRound)+"Data","PapyrusRounds");
    }
    
    SetQuantity(allData.size());
    PushEmpty();
    NormalBarrage();
    isSet=true;
    isAttackEnd=false;
    dogAnimation=1;
    isRightTime=false;
}

void PapyrusRound::PincerAttack(int start,int end,Move* heart, int wave, int appearance,Character *character)
{
    int q=2;
    switch (appearance)
    {
    case normal:
        for(int i=0;i<wave-1;i++)
        {
            if(DetectCertainPoint(enemyBarrage[i*2],940,back)||DetectLeft(enemyBarrage[i*2],vanish))
            {
                q+=2;
            }
        }

        for(int i=start;i<start+q;i++)
        {
            if(i%2==0)
            {
                GoRight(enemyBarrage[i],heart,allData[i].speed,character);
            }
            else
            {
                GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
            }
        }
        break;
    case compoundUp:
    case compoundDown:
        for(int i=0;i<wave-1;i++)
        {
            if(DetectCertainPoint(enemyBarrage[i*4],940,back)||DetectLeft(enemyBarrage[i*4],vanish))
            {
                q+=4;
            }
        }
        
        for(int i=start;i<start+q;i+=4)
        {
            GoRight(enemyBarrage[i],heart,allData[i].speed,character);
            GoRight(enemyBarrage[i+1],heart,allData[i+1].speed,character);
            if(appearance==compoundUp)
            {
                CompoundBarrage(enemyBarrage[i+1],enemyBarrage[i],heart);
                UpDownBarrage(enemyBarrage[i],allData[i].initY-60,825,4);
            }
            else if(appearance==compoundDown)
            {
                CompoundBarrage(enemyBarrage[i],enemyBarrage[i+1],heart);
                UpDownBarrage(enemyBarrage[i+1],allData[i+1].initY-50,allData[i+1].initY+50,4);
            }
            
            GoLeft(enemyBarrage[i+2],heart,allData[i+2].speed,character);
            GoLeft(enemyBarrage[i+3],heart,allData[i+3].speed,character);

            if(appearance==compoundUp)
            {
                CompoundBarrage(enemyBarrage[i+3],enemyBarrage[i+2],heart);
                UpDownBarrage(enemyBarrage[i+2],allData[i+2].initY-60,825,4);
            }
            else if(appearance==compoundDown)
            {
                CompoundBarrage(enemyBarrage[i+2],enemyBarrage[i+3],heart);
                UpDownBarrage(enemyBarrage[i+3],allData[i+3].initY-50,allData[i+3].initY+50,4);
            }
        }
        break;
    }
}

void PapyrusRound::CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart)
{
    if(barrage.GetIsOverlay(heart)||DetectLeft(barrage,vanish))
    {
        cover.set_positon(0,0);
    }
}

void PapyrusRound::UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed)
{
    if(barrage.GetOnePosition(IMGtop)==0)
    {
        return;
    }
    switch (UDBdirection)
    {
    case goUp:
        if(barrage.GetOnePosition(IMGtop)>=upLimit)
        {
            barrage.up_move(speed);
        }
        else if(barrage.GetOnePosition(IMGtop)<upLimit)
        {
            UDBdirection=goDown;
        }
        break;
        
    case goDown:
        if(barrage.GetOnePosition(IMGtop)<=downLimit)
        {
            barrage.down_move(speed);
        }
        else if(barrage.GetOnePosition(IMGtop)>downLimit)
        {
            UDBdirection=goUp;
        }
        break;
    }
}

void PapyrusRound::DetectRoundEnd(int direction)
{
    switch (direction)
    {
    case leftAtLeft:
        if(LeaveAtLeft()||LastOneDisappear())
        {
            currentRound+=1;
            isSet=false;
            isAttackEnd = true;
            
        }
        break;
    case leftAtRight:
        if(LeaveAtRight()||LastOneDisappear())
        {
            currentRound+=1;
            isSet=false;
            isAttackEnd = true;
        }
        break;
    }
}

int PapyrusRound::GetCurrentRound()
{
    return currentRound;
}

void PapyrusRound::DogAnimation(Move *heart,Character *character)
{
    if(currentRound!=20 || !isRightTime)
    {
        return;
    }

    switch (dogAnimation)
    {
    case 1:
    case 2:
        enemyBarrage[0].barrage_img.ShowBitmap();
        enemyBarrage[0].barrage_img.SetAnimation(150,false);
        break;
    case 3:
        enemyBarrage[0].UnshowIMG();
        enemyBarrage[0].set_positon(2000,2000);
        enemyBarrage[1].barrage_img.SetFrameIndexOfBitmap(0);
        enemyBarrage[1].barrage_img.SetTopLeft(1000,810);
        break;
    case 4:
    case 5:
        enemyBarrage[1].barrage_img.SetFrameIndexOfBitmap(1);
        break;
    case 6:
        enemyBarrage[1].UnshowIMG();
        enemyBarrage[1].set_positon(2000,2000);
        enemyBarrage[2].barrage_img.SetTopLeft(1000,810);
        dogAnimation+=1;
        break;
    default:
        enemyBarrage[2].barrage_img.ShowBitmap();
        enemyBarrage[2].barrage_img.SetAnimation(150,false);
        GoRight(enemyBarrage[2],heart,3,character);
        break;
    }
}

void PapyrusRound::HPcondition(Move* heart, Character* character,int command)
{
    if(currentRound==20)
    {
        GetMinusHP_M(heart,character,appear);
    }
    else
    {
        GetMinusHP_M(heart,character,disappear);
    }
}

void PapyrusRound::ToGetEnterCount(UINT nChar)
{
    if(!isRightTime)
    {
        return;
    }
    if(nChar==VK_RETURN && currentRound==20)
    {
        dogAnimation+=1;
    }
}

void PapyrusRound::SelectRound(Move *heart,Character *character,int selection)
{
    switch (currentRound)
    {
    case -1:
        roundX(heart,character);
        break;
    case 0:
        round0(heart,character);
        break;
    case 1:
        round1(heart,character);
        break;
    case 2:
        round2(heart,character);
        break;
    case 3:
        round3(heart,character);
        break;
    case 4:
        round4(heart,character);
        break;
    case 5:
        round5(heart,character);
        break;
    case 6:
        round6(heart,character);
        break;
    case 7:
        round7(heart,character);
        break;
    case 8:
        round8(heart,character);
        break;
    case 9:
        round9(heart,character);
        break;
    case 10:
        round10(heart,character);
        break;
    case 11:
        round11(heart,character);
        break;
    case 12:
        round12(heart,character);
        break;
    case 13:
        round13(heart,character);
        break;
    case 14:
        round14(heart,character);
        break;
    case 15:
        round15(heart,character);
        break;
    case 16:
        round16(heart,character);
        break;
    case 17:
        round17(heart,character);
        break;
    case 18:
        round18(heart,character);
        break;
    case 19:
        round19(heart,character);
        break;
    case 20:
        round20(heart,character);
        break;
    case 21:
        round21(heart,character);
        break;
    }
    
}

void PapyrusRound::roundX(Move *heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round0(Move *heart,Character *character)
{
    for(int i=0;i<_quantity-1;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    if(DetectCertainPoint(enemyBarrage[_quantity-2],665,front)||DetectCertainPoint(enemyBarrage[_quantity-3],665,front))
    {
        GoRight(enemyBarrage[_quantity-1],heart,allData[_quantity-1].speed,character);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round1(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round2(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round3(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round4(Move* heart,Character *character)
{
    bool temp=false;
    for(int i=0;i<_quantity-1;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed,character);
        if(DetectCertainPoint(enemyBarrage[_quantity-2],1250,back))
        {
            temp=true;
        }
    }
    
    if(temp)
    {
        GoLeft(enemyBarrage[_quantity-1],heart,allData[_quantity-1].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round5(Move* heart,Character *character)
{
    bool secondWave=false, thirdWave=false;

    for(int i=0;i<2;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed,character);
        if(DetectCertainPoint(enemyBarrage[0],950,back)||DetectLeft(enemyBarrage[0],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[2],heart,allData[2].speed,character);
        if(DetectCertainPoint(enemyBarrage[2],990,front)||DetectLeft(enemyBarrage[2],vanish))
        {
            thirdWave=true;
        }
    }

    if(thirdWave)
    {
        for(int i=3;i<_quantity;i++)
        {
            GoRight(enemyBarrage[i],heart,allData[i].speed,character);
        }
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round6(Move* heart,Character *character)
{
    bool secondWave=false, thirdWave=false;

    for(int i=0;i<9;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed,character);
        if(DetectCertainPoint(enemyBarrage[8],1110,back)||DetectLeft(enemyBarrage[8],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[9],heart,allData[9].speed,character);
        if(DetectCertainPoint(enemyBarrage[9],750,front)||DetectLeft(enemyBarrage[9],vanish))
        {
            thirdWave=true;
        }
    }

    if(thirdWave)
    {
        GoRight(enemyBarrage[10],heart,allData[10].speed,character);
        GoRight(enemyBarrage[11],heart,allData[11].speed,character);
        GoLeft(enemyBarrage[12],heart,allData[12].speed,character);
        GoLeft(enemyBarrage[13],heart,allData[13].speed,character);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round7(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round8(Move* heart,Character *character)
{
    PincerAttack(0,_quantity,heart,3,normal,character);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round9(Move* heart,Character *character)
{
    PincerAttack(0,_quantity,heart,4,normal,character);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round10(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round11(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
        CompoundBarrage(enemyBarrage[11],enemyBarrage[12],heart);
        CompoundBarrage(enemyBarrage[14],enemyBarrage[13],heart);
        CompoundBarrage(enemyBarrage[15],enemyBarrage[16],heart);
        CompoundBarrage(enemyBarrage[18],enemyBarrage[17],heart);
    }
    
    UpDownBarrage(enemyBarrage[12],422,522,2);
    UpDownBarrage(enemyBarrage[13],742,842,2);
    UpDownBarrage(enemyBarrage[16],385,485,4);
    UpDownBarrage(enemyBarrage[17],703,803,4);

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round12(Move* heart,Character *character)
{
    bool secondWave=false;
    for(int i=0;i<13;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed,character);
        if(DetectLeft(enemyBarrage[12],leftAtRight)||DetectLeft(enemyBarrage[12],vanish)){
            secondWave=true;
        }
    }

    if(secondWave)
    {
        for(int i=13;i<_quantity;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
        }
        CompoundBarrage(enemyBarrage[14],enemyBarrage[13],heart);
        CompoundBarrage(enemyBarrage[16],enemyBarrage[15],heart);
        CompoundBarrage(enemyBarrage[18],enemyBarrage[17],heart);

        UpDownBarrage(enemyBarrage[13],allData[13].initY-50,825,4);
        UpDownBarrage(enemyBarrage[15],allData[15].initY-50,825,4);
        UpDownBarrage(enemyBarrage[17],allData[17].initY-50,825,4);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round13(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round14(Move* heart,Character *character)
{
    bool secondWave=false;
    for(int i=0;i<7;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed+2,character);
        if(DetectCertainPoint(enemyBarrage[6],1095,back)||DetectLeft(enemyBarrage[6],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave){
        for(int i=7;i<_quantity;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed+4,character);
        }
    }
    
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round15(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+2,character);
    }
    CompoundBarrage(enemyBarrage[1],enemyBarrage[0],heart);
    CompoundBarrage(enemyBarrage[3],enemyBarrage[2],heart);
    CompoundBarrage(enemyBarrage[5],enemyBarrage[4],heart);
    UpDownBarrage(enemyBarrage[0],allData[0].initY-50,allData[0].initY+50,6);
    UpDownBarrage(enemyBarrage[2],allData[2].initY-50,allData[2].initY+50,7);
    UpDownBarrage(enemyBarrage[4],allData[4].initY-50,allData[4].initY+50,8);
    
    CompoundBarrage(enemyBarrage[6],enemyBarrage[7],heart);
    CompoundBarrage(enemyBarrage[8],enemyBarrage[9],heart);
    CompoundBarrage(enemyBarrage[10],enemyBarrage[11],heart);
    UpDownBarrage(enemyBarrage[7],allData[7].initY-50,allData[7].initY+10,6);
    UpDownBarrage(enemyBarrage[9],allData[9].initY-50,allData[9].initY+30,7);
    UpDownBarrage(enemyBarrage[11],allData[11].initY-50,allData[11].initY+30,8);

    CompoundBarrage(enemyBarrage[12],enemyBarrage[13],heart);
    UpDownBarrage(enemyBarrage[13],allData[13].initY-40,allData[13].initY+100,3);
    
    CompoundBarrage(enemyBarrage[15],enemyBarrage[16],heart);
    UpDownBarrage(enemyBarrage[16],allData[16].initY-40,allData[16].initY+130,3);

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round16(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+3,character);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round17(Move* heart,Character *character)
{
    PincerAttack(0,_quantity,heart,4,normal,character);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round18(Move* heart,Character *character)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+2,character);
    }

    CompoundBarrage(enemyBarrage[11],enemyBarrage[12],heart);
    CompoundBarrage(enemyBarrage[14],enemyBarrage[13],heart);
    CompoundBarrage(enemyBarrage[15],enemyBarrage[16],heart);
    CompoundBarrage(enemyBarrage[18],enemyBarrage[17],heart);

    UpDownBarrage(enemyBarrage[12],allData[12].initY-50,allData[12].initY+50,4);
    UpDownBarrage(enemyBarrage[13],allData[13].initY-50,allData[13].initY+50,4);
    UpDownBarrage(enemyBarrage[16],allData[16].initY-50,allData[16].initY+50,4);
    UpDownBarrage(enemyBarrage[17],allData[17].initY-50,allData[17].initY+50,4);
    
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round19(Move* heart,Character *character)
{
    PincerAttack(0,_quantity,heart,4,normal,character);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round20(Move* heart,Character *character)
{
    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round21(Move* heart,Character *character)
{
    bool secondWave=false, thirdWave=false, fourthWave=false,
    fifthWave=false, sixthWave=false, sevenWave=false, eightWave=false,
    nineWave=false;

    std::vector<bool> Waves;
    // 0 1
    for(int i=0;i<2;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed+2,character);
    }
    
    if(DetectCertainPoint(enemyBarrage[1],940,back)||DetectLeft(enemyBarrage[1],vanish))
    {
        secondWave=true;
    }
    // 2 3
    if(secondWave)
    {
        for(int i=2;i<4;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed+2,character);
        }
        if(DetectCertainPoint(enemyBarrage[3],735,front)||DetectLeft(enemyBarrage[3],vanish))
        {
            thirdWave=true;
        }
    }
    // 4 5
    if(thirdWave)
    {
        PincerAttack(4,5,heart,1,normal,character);
        if(DetectCertainPoint(enemyBarrage[4],810,back)||DetectLeft(enemyBarrage[4],vanish))
        {
            fourthWave=true;
        }
    }
    // 6 7 8 9
    if(fourthWave)
    {
        PincerAttack(6,9,heart,1,compoundUp,character);
        if(DetectCertainPoint(enemyBarrage[7],870,back)||DetectLeft(enemyBarrage[7],vanish))
        {
            fifthWave=true;
        }
    }
    // 10 11 12 13
    if(fifthWave)
    {
        PincerAttack(10,13,heart,1,compoundDown,character);
        if(DetectCertainPoint(enemyBarrage[10],910,back)||DetectLeft(enemyBarrage[10],vanish))
        {
            sixthWave=true;
        }
        
    }

    // 14 15 16 17
    if(sixthWave)
    {
        PincerAttack(14,17,heart,1,compoundUp,character);
        if(DetectCertainPoint(enemyBarrage[14],820,back)||DetectLeft(enemyBarrage[14],vanish))
        {
            sevenWave=true;
        }
    }

    // 18 19 20 21
    if(sevenWave)
    {
        PincerAttack(18,21,heart,1,compoundUp,character);
        if(DetectCertainPoint(enemyBarrage[20],700,front)||DetectLeft(enemyBarrage[18],vanish))
        {
            eightWave=true;
        }
    }

    // 22 23 24 25 26 27
    if(eightWave)
    {
        for(int i=22;i<27;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed+2,character);
        }
        CompoundBarrage(enemyBarrage[23],enemyBarrage[22],heart);
        CompoundBarrage(enemyBarrage[25],enemyBarrage[24],heart);
        CompoundBarrage(enemyBarrage[27],enemyBarrage[26],heart);
        UpDownBarrage(enemyBarrage[22],allData[22].initY-50,allData[22].initY+50,6);
        UpDownBarrage(enemyBarrage[24],allData[24].initY-50,allData[24].initY+50,7);
        UpDownBarrage(enemyBarrage[26],allData[26].initY-50,allData[26].initY+50,8);

        if(DetectCertainPoint(enemyBarrage[26],740,back)||DetectLeft(enemyBarrage[26],vanish))
        {
            nineWave=true;
        }
    }

    if(nineWave)
    {
        
    }

    // dog running tenWave
}
