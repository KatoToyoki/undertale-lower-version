#pragma once

#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "barrage.h"
#include <vector>
#include <cstdlib>

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
    int xPosition[50],yPosition[50];
    std::vector<Barrage> enemyBarrage;
    std::vector<SetData> allData;

public:
    BarrageMode(int quantity)
    {
        _quantity=quantity;
    }
    ~BarrageMode()=default;
    
    void Init();
    void SetAllData();
    void PushEmpty();
    Barrage Setup(SetData data);
    void RandomBarrage();
    void NormalBarrage();
    void ShowBarrage();
    void UnshowBarrage();
    void MovingBarrage(Move *heart, int speed);
};
