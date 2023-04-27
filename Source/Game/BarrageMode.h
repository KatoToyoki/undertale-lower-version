#pragma once

#include "stdafx.h"
#include "barrage.h"
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Library/json.hpp"
using json = nlohmann::json;

// to set init data ( resetting can use it as well)
struct DataSet
{
    int damage=0;
    int speed=0;
    int initX=0,initY=0;
    barrage_mode mode=white;
    std::vector<std::string> imgPath;
};

class BarrageMode
{
private:
    // currently not be used right now, if it really don't use can deleted
    bool _enable;

    // the return value of the damage that character will receive
    // without this, the return only DO ONCE, the last barrages will not be detected even if it is overlay
    int damageToCharacter=0;

protected:
    // how many barrages the enemy attack mode will hava
    int _quantity=0;

    bool isAttackEnd=false;
    
    // to put all barrages setting in this mode
    std::vector<Barrage> enemyBarrage;

    // the init data (to be used with struct SetData)
    std::vector<DataSet> allData;
    
public:
    BarrageMode()=default;
    ~BarrageMode()=default;

    void SetQuantity(int q)
    {
        _quantity=q;
    }
    
    // depends on quantity, push empty barrage in vector enemyBarrage
    void PushEmpty();

    // when getting a string from json, you will get "sth"
    // need this in order to get rid of two "  
    std::string HandleJsonString(std::string str);

    // in json file, it only have the name of img,
    // not including path and .bmp, so it will add all for you
    void FormatImgPath(std::vector<std::string> &imgArr);

    // you may have multiple img in one CMovingBitmap,
    // it will iterate all paths, and stored for you
    void HandleMultImg(nlohmann::basic_json<> imgArr, std::vector<std::string>& img);

    // to get data from json file, need to input which round so that it can find the name in json
    void HandleJsonData(std::string round);

    // set each barrage in vector enemyBarrage
    Barrage Setup(DataSet data);

    // you can randomly generate barrages
    // should be virtual function MAYBE
    void RandomBarrage();

    // generate barrages by allData order
    void NormalBarrage();

    // show all barrages
    void ShowBarrage();

    // close all barrages
    void UnshowBarrage();

    // getter
    bool GetIsAttackEnd();

    // to return the damage that character will receive
    // i separated this with MovingBarrage because Character must call this function to get the damage
    // meanwhile, MovingBarrage just do move, detection is not its job
    int GetMinusHP_M(Move *heart, int command=appear);

    // to check if this round is end or not
    bool LeaveAtRight();
    bool LeaveAtLeft();
    bool LastOneDisappear();

    void RevealBarrage();
    
    // test print function, will be deleted afterwards
    void Test2()
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 100, 200, "Q "+to_string(damageToCharacter));
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
