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
    int speed=0;
    barrage_mode mode=white;
    std::string imgPath;
    int initX=0,initY=0;
};

class BarrageMode
{
private:
    // currently not be used right now, if it really don't use can deleted
    bool _enable;

protected:
    // how many barrages the enemy attack mode will hava
    int _quantity=0;

    bool isAttackEnd=false;
    
    // for random should check this
    // it can check the ith barrage should placed in the ith x or y
    // so that it won't many barrages in the same position
    
    std::vector<int> xPosition,yPosition, allDamage, allSpeed;

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
    
    // each round may be different, so it's pure virtual
    // set each barrage data, like struct SetData
    virtual void SetAllData()=0;

    // depends on quantity, push empty barrage in vector enemyBarrage
    void PushEmpty();

    // each round may be different, so it's pure virtual
    // if you may need to let x, y, damage, speed stored in array and use index to read them, use this
    virtual void recordXYDamageSpeed()=0;

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

    // to let enemy attack you, each round may be different, so it's pure virtual
    virtual void MovingBarrage(Move *heart)=0;

    bool GetIsAttackEnd();

    int GetMinusHP_M(Move *heart);

    // test print function, will be deleted afterwards
    void Test2()
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 100, 200, "Q "+to_string(_quantity));
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
