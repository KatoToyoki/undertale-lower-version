#pragma once

#include <string>

#include "move.h"
#include "../Library/gameutil.h"

enum barrage_mode
{
    white,
    blue
};

class Barrage
{
public:
    Barrage(int damege = 2, barrage_mode mode = white);
    void load_img(std::string bmp_name);
    void loda_CMoving_Bitmap(game_framework::CMovingBitmap img);
    void up_move(int move_pixel = 7);
    void down_move(int move_pixel = 7);
    void left_move(int move_pixel = 7);
    void right_move(int move_pixel = 7);

    void set_positon(int x, int y);
    void set_show_enable(bool enable);
    void show_img();

    void switch_mode();
    int damege_hit(Move *heart);

private:
    game_framework::CMovingBitmap barrage_img;
    int _damege;
    bool _enable = false;
    barrage_mode _mode;
};
