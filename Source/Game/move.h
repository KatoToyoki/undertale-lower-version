#pragma once

#include "frame.h"
#include "../Library/gameutil.h"

struct Vec2
{
    float x,y;
};


class Move
{
public:
    void load_img();
    void check_range(Corner corner);
    
    void move_control();
    void move_act(Vec2 force);

    
    game_framework::CMovingBitmap heart;
private:
    Vec2 normalize(Vec2 force);
    
    bool stop_postion_up = true;
    bool stop_postion_down = true;
    bool stop_postion_left = true;
    bool stop_postion_right = true;
    bool stop = true;

    int move_num = 10;

};
