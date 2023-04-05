#pragma once

#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "barrage.h"
#include <vector>

struct SetData
{
    int damage=0;
    barrage_mode mode=white;
    std::string imgPath;
    int initX=0,initY=0;
};

class BarrageMode
{
private:
    bool _enable;
    int _quantity=0;
    // Barrage *enemyBarrage;
    std::vector<Barrage> enemyBarrage;
    //SetData *allData;
    std::vector<SetData> allData;

public:
    BarrageMode(int quantity)
    {
        _quantity=quantity;
        //enemyBarrage= new Barrage[quantity];
        //allData = new SetData[quantity];
    }
    ~BarrageMode()
    {
        //delete [] enemyBarrage;
        //delete [] allData;
    }
    
    void RevealBarrage(Move *heart, Barrage *current, int speed);
    void SetUp(Barrage *current, SetData *data);
    void ShowBarrage();
    void UnshowBarrage();

    void SetAllData();
};
