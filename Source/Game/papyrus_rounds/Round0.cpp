#include "stdafx.h"
#include "Round0.h"

void Round0::SetAllData()
{
    HandleJsonData("Round0Data");
}

void Round0::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity-1;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allData[i].speed);
    }

    if(enemyBarrage[_quantity-2].GetOnePosition(IMGleft)<665 && enemyBarrage[_quantity-3].GetOnePosition(IMGleft)<665)
    {
        enemyBarrage[_quantity-1].set_show_enable(true);
        enemyBarrage[_quantity-1].damege_hit(heart,disappear);
        enemyBarrage[_quantity-1].right_move(allData[_quantity-1].speed);
    }

    if(LeaveAtRight()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}