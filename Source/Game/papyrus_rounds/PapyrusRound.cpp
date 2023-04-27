#include "stdafx.h"
#include "PapyrusRound.h"

void PapyrusRound::SetAllData()
{
    allData.clear();
    allData.shrink_to_fit();
    enemyBarrage.clear();
    enemyBarrage.shrink_to_fit();

    _q++;
    
    if(currentRound==-1)
    {
        HandleJsonData("RoundXData");    
    }
    else
    {
        HandleJsonData("Round"+to_string(currentRound)+"Data");
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

void PapyrusRound::CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart)
{
    if(barrage.GetIsOverlay(heart))
    {
        cover.set_positon(0,0);
    }
}

void PapyrusRound::UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed)
{
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
        return barrage.GetOnePosition(IMGleft)>1250;
    case leftAtRight:
        return barrage.GetOnePosition(IMGleft)<650;
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
