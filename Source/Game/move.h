#pragma once

#include "frame.h"
#include "../Library/gameutil.h"

struct Vec2
{
    float x,y;
};

enum HeartMode
{
    heart_red,
    heart_blue
};


class Move
{
public:
    Move()
    {
        move_num_x = 8.5;
        move_num_y = 8.5;
    }
    void load_img();
    void move_control(Corner corner,bool enable);
    void set_show_img_enable(bool enable);
    void set_heart_jump_enable_and_init(bool enable);
    void set_heart_postion(int x, int y);
    void set_shine_mode(bool enable);
    void set_heart_mode(HeartMode heart_mode = heart_red);
    void show_heart_img();

    void shine_two_second();
    void shine_count();
    
    game_framework::CMovingBitmap heart;
	DWORD shine_time_count =1000;
	DWORD jump_time_count;
	DWORD jump_time_count_max_up;
	DWORD jump_time_count_max_down;
	DWORD max_init = 450;

    int GetCurrentX();
    int GetCurrentY();
    bool _shine_mode = false;
private:
    Vec2 check_range(Corner corner,Vec2 force);
    Vec2 normalize(Vec2 force);
    void move_act(Vec2 force);
    Vec2 red_mode();
    Vec2 blue_mode();

    float move_num_x;
    float move_num_y;
    bool _enable_img = false;
    bool _enable_move = false;
    bool _enable_blue_heart_jump = false;
    
    HeartMode _heart_mode;// = heart_red;
};
