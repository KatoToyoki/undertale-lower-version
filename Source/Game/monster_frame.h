#pragma once

#include "game_text.h"
#include "text.h"
#include "../Library/gameutil.h"

class MonsterFrame
{
public:
    void load_img();
    void load_game_text(GameText game_text);
    void show_monster_frame_and_print();
    void set_img_position(int x, int y);
    void set_enable(bool enable,int head =0 , int text_len =1);
    
private:
    game_framework::CMovingBitmap monster_frame_img;
    bool _enable = false;
    GameText _game_text;

    DWORD _time_count = 0;
    
};
