#include "stdafx.h"
#include "Round11.h"

void Round11::SetAllData()
{
    HandleJsonData("Round11Data");
}

void Round11::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allData[i].speed);

        if(enemyBarrage[13].GetIsOverlay(heart))
        {
            enemyBarrage[14].set_positon(0,0);
        }
    }
   
    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd=true;
    }
}