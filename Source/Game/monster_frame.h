#pragma once

#include "game_text.h"
#include "text.h"
#include "../Library/gameutil.h"
#include <random>

enum monster_frame_mode
{
    no_enter_talk,
    enter_talk,
    pass_talk
};

class MonsterFrame
{
public:
    void load_img();
    void load_game_text_and_mode(GameText game_text,int mode = no_enter_talk);
    void show_monster_frame_and_print();
    void set_img_position(int x, int y);
    void set_enable(bool enable);
    
    bool _monster_saying_is_done = true;
    DWORD _time_count = 0;
private:
    game_framework::CMovingBitmap monster_frame_img;
    bool _enable = false;
    GameText _game_text;

    int _mode = 0;
};
