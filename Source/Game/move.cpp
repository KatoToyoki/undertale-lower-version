#include "stdafx.h"
#include "move.h"

void Move::load_img()
{
    heart.LoadBitmapByString({"resources/heart.bmp"},RGB(255,255,255));
    heart.SetTopLeft(1000,100);
}

UINT Move::check_press(UINT nChar)
{
    _nChar = nChar;    
    if (press == false)
    {
        press = true;
    }
    else
    {
        press = false;
    }
    return nChar;
}

void Move::move_control()
{
    if (press == true)
    {
        if (_nChar == VK_UP )
        {
            heart.SetTopLeft(heart.GetLeft(),heart.GetTop()-10);
        }
        if (_nChar == VK_DOWN)
        {
            heart.SetTopLeft(heart.GetLeft(),heart.GetTop()+10);
        }
        if (_nChar == VK_RIGHT)
        {
            heart.SetTopLeft(heart.GetLeft()+10,heart.GetTop());
        }
        if (_nChar == VK_LEFT)
        {
            heart.SetTopLeft(heart.GetLeft()-10,heart.GetTop());
        }
    }
}

