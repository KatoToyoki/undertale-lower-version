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
    Move()
    {
        move_num = 7.0;
    }
    void load_img();
    void move_control(Corner corner,bool enable);
    void set_heart_postion(int x, int y);
    void show_heart_img();

    void shine_two_second();
    
    game_framework::CMovingBitmap heart;
	DWORD time_count =0;
private:
    Vec2 check_range(Corner corner,Vec2 force);
    Vec2 normalize(Vec2 force);
    void move_act(Vec2 force);

    float move_num;
    bool _enable = false;
    bool _shine_mode = false;
};
