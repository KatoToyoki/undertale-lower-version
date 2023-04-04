#include "stdafx.h"
#include "barrage.h"
#include "../Library/gamecore.h"

Barrage::Barrage(int damege, barrage_mode mode)
{
    _damege = damege;
    _mode = mode;
}

void Barrage::up_move(int move_pixel)
{
    barrage_img.SetTopLeft(barrage_img.GetLeft(),barrage_img.GetTop()-move_pixel);
}

void Barrage::down_move(int move_pixel)
{
    barrage_img.SetTopLeft(barrage_img.GetLeft(),barrage_img.GetTop()+move_pixel);
}

void Barrage::left_move(int move_pixel)
{
    barrage_img.SetTopLeft(barrage_img.GetLeft() - move_pixel,barrage_img.GetTop());
}

void Barrage::right_move(int move_pixel)
{
    barrage_img.SetTopLeft(barrage_img.GetLeft() + move_pixel,barrage_img.GetTop());
}

void Barrage::set_positon(int x, int y)
{
    barrage_img.SetTopLeft(x,y);
}

void Barrage::load_img(std::string bmp_name)
{
    if (_mode == white)
    {
        barrage_img.LoadBitmapByString({"resources/"+bmp_name+".bmp"});
    }
    else
    {
        barrage_img.LoadBitmapByString({"resources/"+bmp_name+".bmp"},RGB(255,255,255));
    }
}

void Barrage::loda_CMoving_Bitmap(game_framework::CMovingBitmap img)
{
    barrage_img = img;
}


void Barrage::set_show_enable(bool enable)
{
    _enable = enable;
}

void Barrage::show_img()
{
    if (_enable)
    {
        barrage_img.ShowBitmap();
    }
}

void Barrage::switch_mode()
{
    if (_mode == white)
    {
        _mode = blue;
    }
    else
    {
        _mode = white;
    }
}

int Barrage::damege_hit(Move *heart)
{
    if (_mode == white && barrage_img.IsOverlap(barrage_img,heart->heart))
    {
        heart->time_count = 0;
        heart->shine_two_second();
        return _damege;
    }
    if (_mode == blue)
    {
        if (GetKeyState(VK_UP)&0x8000 || GetKeyState(VK_DOWN)&0x8000 ||
            GetKeyState(VK_LEFT)&0x8000 || GetKeyState(VK_RIGHT)&0x8000)
        {
            if (barrage_img.IsOverlap(barrage_img,heart->heart))
            {
                heart->time_count = 0;
                heart->shine_two_second();
                return  _damege;
            }
        }
    }
    heart->shine_two_second();
    return 0;
}

