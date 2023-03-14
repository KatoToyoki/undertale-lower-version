#pragma once

#include "../Library/gameutil.h"

class MonsterFrame
{
public:
    void load_img();
    void print_text();
    void show_monster_img();
private:
    game_framework::CMovingBitmap monster_frame_img;
    
};
