#pragma once

#include <string>
#include "../Library/gameutil.h"

class Charactor
{
public:
    void change_hp(bool enable,int heal_or_damege = 0);
    void change_hp_updata(UINT nChar);
    void set_hp_img();
    void show_charactor_data();
    void updata_hp_bar_by_hp();

private:
    std::string name = "Frisk";
    int level = 1;
    int exp = 0;
    int hp_max = 50;
    int hp = 10;
    int one_hp_pixel = 3;
    int hp_bar_position_x = 859;
    int hp_bar_position_y = 900;
    int max_bar_position_x = hp_bar_position_x + (one_hp_pixel * hp_max);
    bool change_hp_enable = false;
    int _heal_or_damege = 0;

    game_framework::CMovingBitmap hp_bar;
    game_framework::CMovingBitmap hp_bar_red;
    game_framework::CMovingBitmap hp_bar_black;
};
