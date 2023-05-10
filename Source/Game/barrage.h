#pragma once

#include <string>

#include "Character.h"
#include "move.h"
#include "../Library/gameutil.h"

enum barrage_mode
{
    white,
    blue
};

enum isDisappear
{
    appear,
    disappear
};

enum imgDirection
{
    IMGleft,
    IMGtop,
};

class Barrage
{
public:
    Barrage(int damege = 2, barrage_mode mode = white);
    void load_img(std::string bmp_name);
    void loda_CMoving_Bitmap(game_framework::CMovingBitmap img);
    void LoadMultImg(std::vector<std::string> imgArr);
    void up_move(int move_pixel = 7);
    void down_move(int move_pixel = 7);
    void left_move(int move_pixel = 7);
    void right_move(int move_pixel = 7);

    void set_positon(int x, int y);
    void set_show_enable(bool enable);
    void SetDamage(int damage);
    void SetMode(barrage_mode mode);
    
    void show_img();
    void UnshowIMG();
    
    void switch_mode();
    
    void damege_hit(Move *heart,Character *character, int command=appear);

    int GetOnePosition(int direction);

    bool GetIsOverlay(Move *heart);

    game_framework::CMovingBitmap barrage_img;

private:
    int _damage;
    bool _enable = false;
    barrage_mode _mode;
};
