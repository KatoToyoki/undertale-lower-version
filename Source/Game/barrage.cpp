#include "stdafx.h"
#include "barrage.h"

#include "game_text.h"
#include "../Library/gamecore.h"

Barrage::Barrage(int damege, barrage_mode mode)
{
    _damage = damege;
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
        barrage_img.LoadBitmapByString({"resources/"+bmp_name+".bmp"},RGB(255,255,255));
        barrage_img.LoadBitmapByString({"resources/"+bmp_name+".bmp"},RGB(0,0,0));
    }
    else
    {
        barrage_img.LoadBitmapByString({"resources/"+bmp_name+".bmp"},RGB(255,255,255));
    }
}

void Barrage::LoadMultImg(std::vector<std::string> imgArr)
{
    barrage_img.LoadBitmapByString(imgArr,RGB(255,255,255));
}


void Barrage::loda_CMoving_Bitmap(game_framework::CMovingBitmap img)
{
    barrage_img = img;
}


void Barrage::set_show_enable(bool enable)
{
    _enable = enable;
}

void Barrage::SetDamage(int damage)
{
    _damage=damage;
}

void Barrage::SetMode(barrage_mode mode)
{
    _mode=mode;
}

void Barrage::show_img()
{
    if (_enable)
    {
        barrage_img.ShowBitmap();
    }
}

void Barrage::UnshowIMG()
{
    if (_enable)
    {
        barrage_img.UnshowBitmap();
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

void Barrage::damege_hit(Move *heart, Character *character,int command)
{
    if (_mode == white && barrage_img.IsOverlap(barrage_img,heart->heart) && heart -> shine_time_count >=400)
    {
        heart->shine_time_count = 0;
        heart->shine_two_second();
        
        character->change_hp(true,_damage*(-1));

        if(command==disappear)
        {
            barrage_img.SetTopLeft(0,0);
        }
        return;
    }
    if (_mode == blue)
    {
        if (GetKeyState(VK_UP)&0x8000 || GetKeyState(VK_DOWN)&0x8000 ||
            GetKeyState(VK_LEFT)&0x8000 || GetKeyState(VK_RIGHT)&0x8000)
        {
            if (barrage_img.IsOverlap(barrage_img,heart->heart) && heart -> shine_time_count >=400 )
            {
                heart->shine_time_count = 0;
                heart->shine_two_second();
                
                barrage_img.SetTopLeft(0,0);
                character->change_hp(true,_damage*(-1));

                if(command==disappear)
                {
                    barrage_img.SetTopLeft(0,0);
                }
                return;
            }
        }
    }
    heart->shine_two_second();
    return ;
}

int Barrage::GetOnePosition(int direction)
{
    switch (direction)
    {
    case IMGleft:
        return barrage_img.GetLeft();
    case IMGtop:
        return barrage_img.GetTop();
    }
    return 0;
}

bool Barrage::GetIsOverlay(Move* heart)
{
    return barrage_img.IsOverlap(barrage_img,heart->heart);
}