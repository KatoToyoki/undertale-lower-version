#include "stdafx.h"
#include "Round6.h"

void Round6::SetAllData()
{
    HandleJsonData("Round6Data");
}

void Round6::MovingBarrage(Move* heart)
{
    for(int i=0;i<9;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allData[i].speed);
        if(enemyBarrage[8].GetOnePosition(IMGleft)>1110)
        {
            SecondWave(heart);
        }
    }
}

void Round6::SecondWave(Move* heart)
{
    enemyBarrage[9].set_show_enable(true);
    enemyBarrage[9].damege_hit(heart,disappear);
    enemyBarrage[9].left_move(1);

    if(enemyBarrage[9].GetOnePosition(IMGleft)<750)
    {
        ThirdWave(heart);
    }
}

void Round6::ThirdWave(Move* heart)
{
    for(int i=10;i<14;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);

        switch (i)
        {
        case 10:
        case 11:
            enemyBarrage[i].right_move(allData[i].speed);
            break;

        case 12:
        case 13:
            enemyBarrage[i].left_move(allData[i].speed);
            break;    
        }
    }
    
    if((enemyBarrage[10].GetOnePosition(IMGleft)>1270||enemyBarrage[11].GetOnePosition(IMGleft)>1270)||(enemyBarrage[12].GetOnePosition(IMGleft)<650||enemyBarrage[13].GetOnePosition(IMGleft)<650)){
        isAttackEnd=true;
    }
}

