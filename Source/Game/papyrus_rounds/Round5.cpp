#include "stdafx.h"
#include "Round5.h"

void Round5::SetAllData()
{
    HandleJsonData("Round5Data");
}

void Round5::MovingBarrage(Move* heart)
{
    for(int i=0;i<2;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allData[i].speed);
        if(enemyBarrage[0].GetOnePosition(IMGleft)>950||enemyBarrage[1].GetOnePosition(IMGleft)>950)
        {
            SecondWave(heart);
        }
    }

    if(LeaveAtRight()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}

void Round5::SecondWave(Move* heart)
{
    enemyBarrage[2].set_show_enable(true);
    enemyBarrage[2].damege_hit(heart,disappear);
    enemyBarrage[2].left_move(allData[2].speed);
    if(enemyBarrage[2].GetOnePosition(IMGleft)<990)
    {
        ThirdWave(heart);
    }
}

void Round5::ThirdWave(Move* heart)
{
    for(int i=3;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allData[i].speed);
    }

    if(LeaveAtRight()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}
