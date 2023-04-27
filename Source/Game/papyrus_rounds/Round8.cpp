#include "stdafx.h"
#include "Round8.h"

void Round8::SetAllData()
{
    HandleJsonData("Round8Data");
}

void Round8::MovingBarrage(Move* heart)
{
    int q=2;
    if(enemyBarrage[0].GetOnePosition(IMGleft)>940||enemyBarrage[0].GetOnePosition(IMGtop)==0)
    {
        q=4;
    }
    if(enemyBarrage[2].GetOnePosition(IMGleft)>940||enemyBarrage[2].GetOnePosition(IMGtop)==0)
    {
        q=6;
    }
    
    for(int i=0;i<q;i++)
    {
        if(i%2==0)
        {
            enemyBarrage[i].set_show_enable(true);
            enemyBarrage[i].damege_hit(heart,disappear);
            enemyBarrage[i].right_move(allData[i].speed);
        }
        else
        {
            enemyBarrage[i].set_show_enable(true);
            enemyBarrage[i].damege_hit(heart,disappear);
            enemyBarrage[i].left_move(allData[i].speed);
        }
    }
   
    if((LeaveAtLeft()||LastOneDisappear()))
    {
        isAttackEnd=true;
    }
}