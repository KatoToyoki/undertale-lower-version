#pragma once
#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <iostream>

enum fightRange
{
    /*
     * range : 431~1540
     * 0.0 - 0.1 - 0.3 - 0.46 - 0.54 - 0.7 - 0.9 - 1.0
     *   0.15   0.18   0.18  0.24  0.21  0.18   0.15  
     */
    theStart=431,thirdFront=542,secondFront=764,firstFront=940,firstBehind=1028,secondBehind=1204,thirdBehind=1426,theEnd=1520
};

enum MonsterFull
{
    test=1000
};

class Fight
{
private:
    bool _enable;
    game_framework::CMovingBitmap fightScope,fightBar;
    game_framework::CMovingBitmap HPFrame,HP,HPminus;
    bool _isBarStop=false;

    bool _isAttack=false;
    std::string minusHP="";
    int attackCount=0;
    int minusPosition=1300;
   

    // temp testing variable
    int monsterHP=1000;
    int durationMinusHP=80;
    
    
protected:
    
public:
    Fight()=default;
    ~Fight()=default;

    
    int GetAttackCount();
    bool GetIsAttack();
    
    std::string GetMinusHP();
    int GetDurationMinusHP();
    void SetDurationMinusHP();
    void SetMinusHP();
    void SetIsAttack();
    void EndFight();

    void ShowHPBar();
    void UnshowHPBar();

    // REQUIRED
    // load and set img for init
    void load_img();
    
    // REQUIRED
    // put OnMove, can modify enable to control if img will reveal or not
    void show_fight_img();

    // REQUIRED
    // put OnShow, set if the image will be revealed
    void set_fight_img_enable(bool enable);

    // REQUIRED
    // depending on the position, return the value of how much will HP be subtracted
    int attack();

    void MoveingBar();

    // depending on key in, decide if the bar will stop
    void ToStop(UINT nChar, UINT nRepCnt, UINT nFlags);

    void RevealMinusHP();

    //void TTTT();
    
};
