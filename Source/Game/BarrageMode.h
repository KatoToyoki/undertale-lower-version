#pragma once

#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "barrage.h"
#include <vector>
#include <cstdlib>

// to set init data ( resetting can use it as well)
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
    // currently not be used right now, if it really don't use can deleted
    bool _enable;

    // how many barrages the enemy attack mode will hava
    int _quantity=0;

protected:
    // for random should check this
    // it can check the ith barrage should placed in the ith x or y
    // so that it won't many barrages in the same position
    
    std::vector<int> xPosition,yPosition, allDamage;

    // to put all barrages setting in this mode
    std::vector<Barrage> enemyBarrage;

    // the init data (to be used with struct SetData)
    std::vector<SetData> allData;
    
public:
    BarrageMode(int quantity)
    {
        _quantity=quantity;
    }
    ~BarrageMode()=default;

    // it will init everything you need,
    // set xPosition, yPosition depends on each mode
    // kind of virtual function
    void Init();

    // it supposed to be pure virtual function
    // because each mode have different condition
    virtual void SetAllData()=0;

    virtual void PushXYDamage()=0;

    // depends on quantity, push empty barrage in vector enemyBarrage
    void PushEmpty();

    // set each barrage in vector enemyBarrage
    Barrage Setup(SetData data);

    // you can randomly generate barrages
    // should be virtual function MAYBE
    void RandomBarrage();

    // generate barrages by allData order
    void NormalBarrage();

    // show all barrages
    void ShowBarrage();

    // close all barrages
    void UnshowBarrage();

    // to let enemy attack you
    void MovingBarrage(Move *heart, int speed);
};
