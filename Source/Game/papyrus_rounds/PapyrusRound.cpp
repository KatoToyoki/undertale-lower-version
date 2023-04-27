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

void PapyrusRound::PincerAttack(int range, Move* heart, int wave, int appearance)
{
    int q=0;
    switch (appearance)
    {
    case normal:
        for(int i=0;i<=range;i+=2)
        {
            if(DetectCertainPoint(enemyBarrage[i],940,back)||DetectLeft(enemyBarrage[i],vanish))
            {
                q+=2;
            }
        }

        for(int i=0;i<q;i++)
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
        // 0 1 2 3 | 4 5 6 7
        for(int i=0;i<=range;i+=4)
        {
            if(DetectCertainPoint(enemyBarrage[i],940,back)||DetectLeft(enemyBarrage[i],vanish))
            {
                q+=4;
            }
        }

        for(int i=0;i<q;i+=4)
        {
            GoRight(enemyBarrage[i],heart,allData[i].speed);
            GoRight(enemyBarrage[i+1],heart,allData[i+1].speed);
            GoLeft(enemyBarrage[i+2],heart,allData[i+2].speed);
            GoLeft(enemyBarrage[i+3],heart,allData[i+3].speed);
        }
        break;
    }
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
            isAttackEnd = true;
            
        }
        break;
    case leftAtRight:
        if(LeaveAtRight()||LastOneDisappear())
        {
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

void PapyrusRound::SelectRound(Move *heart)
{
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

