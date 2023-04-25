#include "stdafx.h"
#include "Round9.h"

void Round9::SetAllData()
{
    HandleJsonData("Round9Data");
}

void Round9::MovingBarrage(Move* heart)
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
    if(enemyBarrage[4].GetOnePosition(IMGleft)>940||enemyBarrage[4].GetOnePosition(IMGtop)==0)
    {
        q=8;
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
   
    if((q==8)&&(LeaveAtLeft()||LastOneDisappear()))
    {
        isAttackEnd=true;
    }
}