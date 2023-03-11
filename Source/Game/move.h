#pragma once

#include "../Library/gameutil.h"
class Move
{
public:
    void load_img();
    UINT check_press(UINT nChar);
    void move_control();
    
    game_framework::CMovingBitmap heart;
private:
    bool press = false;
    unsigned _nChar;
    
};
