#include "stdafx.h"
#include "PapyrusRound.h"

void PapyrusRound::SetAllData()
{
    allData.clear();
    allData.shrink_to_fit();
    enemyBarrage.clear();
    enemyBarrage.shrink_to_fit();

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
}

void PapyrusRound::GoLeft(Barrage& barrage, Move* heart, int speed)
{
    barrage.set_show_enable(true);
    barrage.damege_hit(heart,disappear);
    barrage.left_move(speed);
}

void PapyrusRound::GoRight(Barrage& barrage, Move* heart, int speed)
{
    barrage.set_show_enable(true);
    barrage.damege_hit(heart,disappear);
    barrage.right_move(speed);
}

void PapyrusRound::PincerAttack(int start,int end,Move* heart, int wave, int appearance)
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
                GoRight(enemyBarrage[i],heart,allData[i].speed);
            }
            else
            {
                GoLeft(enemyBarrage[i],heart,allData[i].speed);
            }
        }
        break;
    case compound:
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

bool  PapyrusRound::DetectLeft(Barrage& barrage,int direction)
{
    switch (direction)
    {
    case leftAtLeft:
        return barrage.GetOnePosition(IMGleft)<650;
    case leftAtRight:
        return barrage.GetOnePosition(IMGleft)>1250;
    case vanish:
        return barrage.GetOnePosition(IMGtop)==0;
    }

    return false;
}

bool PapyrusRound::DetectCertainPoint(Barrage& barrage,int point ,int position)
{
    switch (position)
    {
    case front:
        return barrage.GetOnePosition(IMGleft)<point;
    case back:
        return barrage.GetOnePosition(IMGleft)>point;
    case frontEqual:
        return barrage.GetOnePosition(IMGleft)<=point;
    case backEqual:
        return barrage.GetOnePosition(IMGleft)>=point;
    }
    
    return false;
}

int PapyrusRound::GetCurrentRound()
{
    return currentRound;
}

void PapyrusRound::SelectRound(Move *heart,int selection)
{
    // for test
    if(selection!=-99)
    {
        currentRound=selection;
    }
    
    if(!isSet)
    {
        SetAllData();
    }
    
    switch (currentRound)
    {
    case -1:
        roundX(heart);
        break;
    case 0:
        round0(heart);
        break;
    case 1:
        round1(heart);
        break;
    case 2:
        round2(heart);
        break;
    case 3:
        round3(heart);
        break;
    case 4:
        round4(heart);
        break;
    case 5:
        round5(heart);
        break;
    case 6:
        round6(heart);
        break;
    case 7:
        round7(heart);
        break;
    case 8:
        round8(heart);
        break;
    case 9:
        round9(heart);
        break;
    case 10:
        round10(heart);
        break;
    case 11:
        round11(heart);
        break;
    case 12:
        round12(heart);
        break;
    case 13:
        round13(heart);
        break;
    case 14:
        round14(heart);
        break;
    case 15:
        round15(heart);
        break;
    case 16:
        round16(heart);
        break;
    case 17:
        round17(heart);
        break;
    case 18:
        round18(heart);
        break;
    case 19:
        round19(heart);
        break;
    case 20:
        round20(heart);
        break;
    }
    
}

void PapyrusRound::roundX(Move *heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round0(Move *heart)
{
    for(int i=0;i<_quantity-1;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    if(DetectCertainPoint(enemyBarrage[_quantity-2],665,front)||DetectCertainPoint(enemyBarrage[_quantity-3],665,front))
    {
        GoRight(enemyBarrage[_quantity-1],heart,allData[_quantity-1].speed);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round1(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round2(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round3(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round4(Move* heart)
{
    bool temp=false;
    for(int i=0;i<_quantity-1;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed);
        if(DetectCertainPoint(enemyBarrage[_quantity-2],1250,back))
        {
            temp=true;
        }
    }
    
    if(temp)
    {
        GoLeft(enemyBarrage[_quantity-1],heart,allData[_quantity-1].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round5(Move* heart)
{
    bool secondWave=false, thirdWave=false;

    for(int i=0;i<2;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed);
        if(DetectCertainPoint(enemyBarrage[0],950,back)||DetectLeft(enemyBarrage[0],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[2],heart,allData[2].speed);
        if(DetectCertainPoint(enemyBarrage[2],990,front)||DetectLeft(enemyBarrage[2],vanish))
        {
            thirdWave=true;
        }
    }

    if(thirdWave)
    {
        for(int i=3;i<_quantity;i++)
        {
            GoRight(enemyBarrage[i],heart,allData[i].speed);
        }
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round6(Move* heart)
{
    bool secondWave=false, thirdWave=false;

    for(int i=0;i<9;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed);
        if(DetectCertainPoint(enemyBarrage[8],1110,back)||DetectLeft(enemyBarrage[8],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[9],heart,allData[9].speed);
        if(DetectCertainPoint(enemyBarrage[9],750,front)||DetectLeft(enemyBarrage[9],vanish))
        {
            thirdWave=true;
        }
    }

    if(thirdWave)
    {
        GoRight(enemyBarrage[10],heart,allData[10].speed);
        GoRight(enemyBarrage[11],heart,allData[11].speed);
        GoLeft(enemyBarrage[12],heart,allData[12].speed);
        GoLeft(enemyBarrage[13],heart,allData[13].speed);
    }

    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::round7(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round8(Move* heart)
{
    PincerAttack(0,_quantity,heart,3,normal);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round9(Move* heart)
{
    PincerAttack(0,_quantity,heart,4,normal);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round10(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round11(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
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

void PapyrusRound::round12(Move* heart)
{
    bool secondWave=false;
    for(int i=0;i<13;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed);
        if(DetectLeft(enemyBarrage[12],leftAtRight)||DetectLeft(enemyBarrage[12],vanish)){
            secondWave=true;
        }
    }

    if(secondWave)
    {
        for(int i=13;i<_quantity;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed);
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

void PapyrusRound::round13(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round14(Move* heart)
{
    bool secondWave=false;
    for(int i=0;i<7;i++)
    {
        GoRight(enemyBarrage[i],heart,allData[i].speed+2);
        if(DetectCertainPoint(enemyBarrage[6],1095,back)||DetectLeft(enemyBarrage[6],vanish))
        {
            secondWave=true;
        }
    }

    if(secondWave){
        for(int i=7;i<_quantity;i++)
        {
            GoLeft(enemyBarrage[i],heart,allData[i].speed+4);
        }
    }
    
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round15(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+2);
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

void PapyrusRound::round16(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+3);
    }

    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round17(Move* heart)
{
    PincerAttack(0,_quantity,heart,4,normal);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round18(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        GoLeft(enemyBarrage[i],heart,allData[i].speed+2);
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

void PapyrusRound::round19(Move* heart)
{
    PincerAttack(0,_quantity,heart,4,normal);
    DetectRoundEnd(leftAtLeft);
}

void PapyrusRound::round20(Move* heart)
{
    DetectRoundEnd(leftAtRight);
}

void PapyrusRound::DogAnimation(Move *heart)
{
    if(currentRound!=20)
    {
        return;
    }

    switch (dogAnimation)
    {
    case 1:
        enemyBarrage[0].barrage_img.ShowBitmap();
        enemyBarrage[0].barrage_img.SetAnimation(150,false);
        break;
    case 2:
        enemyBarrage[0].UnshowIMG();
        enemyBarrage[0].set_positon(2000,2000);
        enemyBarrage[1].barrage_img.SetFrameIndexOfBitmap(0);
        enemyBarrage[1].barrage_img.SetTopLeft(1000,810);
        break;
    case 3:
        enemyBarrage[1].barrage_img.SetFrameIndexOfBitmap(1);
        break;
    case 4:
        enemyBarrage[1].UnshowIMG();
        enemyBarrage[1].set_positon(2000,2000);
        enemyBarrage[2].barrage_img.SetTopLeft(1000,810);
        dogAnimation+=1;
        break;
    default:
        enemyBarrage[2].barrage_img.ShowBitmap();
        enemyBarrage[2].barrage_img.SetAnimation(150,false);
        GoRight(enemyBarrage[2],heart,3);
        break;
    }
}

void PapyrusRound::ToGetEnterCount(UINT nChar)
{
    if(nChar==VK_RETURN && currentRound==20)
    {
        dogAnimation+=1;
    }
}

