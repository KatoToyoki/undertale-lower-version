#pragma once
#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

class Fight
{
private:
    bool _enable;
    game_framework::CMovingBitmap fightScope,fightBar;
    bool _isBarStop=false;
    
protected:
    
public:
    Fight()=default;
    ~Fight()=default;

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

    // depending on key in, decide what target is, then do the function on OnShow
    void ToStop(UINT nChar, UINT nRepCnt, UINT nFlags);
    
};
