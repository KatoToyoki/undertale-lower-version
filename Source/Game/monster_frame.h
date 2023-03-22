#pragma once

#include "text.h"
#include "../Library/gameutil.h"

class MonsterFrame
{
public:
    void load_img();
    void show_monster_frame_and_print();
    void set_img_position(int x, int y);
    void set_enable(bool enable);
    
    
    
private:
    game_framework::CMovingBitmap monster_frame_img;
    bool _enable = false;
    Text data;
    Text data2;

    DWORD _time_count = 0;
    
};
