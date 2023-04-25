#include "stdafx.h"
#include "Round4.h"

void Round4::SetAllData()
{
    HandleJsonData("Round4Data");
}

void Round4::LastOneFast(Move* heart)
{
    enemyBarrage[_quantity-1].set_show_enable(true);
    enemyBarrage[_quantity-1].damege_hit(heart,disappear);
    enemyBarrage[_quantity-1].left_move(allData[_quantity-1].speed);
}


void Round4::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity-1;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allData[i].speed);
        if(enemyBarrage[_quantity-2].GetOnePosition(IMGleft)>1250)
        {
            LastOneFast(heart);
            break;
        }
    }

    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}
