#include "stdafx.h"
#include "BarrageMode.h"

void BarrageMode::RevealBarrage(Move *heart, Barrage *current, int speed)
{
    current->set_show_enable(true);
    current->damege_hit(heart);
    current->left_move(speed);
}

void BarrageMode::SetUp(Barrage *current, SetData *data)
{
    *current=Barrage(data->damage,data->mode);
    current->load_img(data->imgPath);
    current->set_positon(data->initX,data->initY);
}

void BarrageMode::ShowBarrage()
{
    for(Barrage *i=enemyBarrage;i<enemyBarrage+_quantity;i++)
    {
        i->show_img();
    }
}

void BarrageMode::UnshowBarrage()
{
    for(Barrage *i=enemyBarrage;i<enemyBarrage+_quantity;i++)
    {
        i->UnshowIMG();
    }
}

void BarrageMode::SetAllData()
{
    SetData *current=allData;
    // ========================================
    current->damage=3;
    current->mode=white;
    current->imgPath="bone1";
    current->initX=1000;
    current->initY=795;

    *allData=*current;
    // ========================================
    current->damage=3;
    current->mode=white;
    current->imgPath="bone2";
    current->initX=1150;
    current->initY=783;

    *(allData+1)=*current;
    // ========================================
    current->damage=3;
    current->mode=white;
    current->imgPath="bone3";
    current->initX=1300;
    current->initY=774;
    
    *(allData+2)=*current;
}




