#include "stdafx.h"
#include "text.h"

#include "mygame.h"

Text::Text(int size, std::string str, COLORREF color, int weight, int x, int y)
{
    _size = size;
    _str = str;
    _color = color;
    _weight = weight;
    set_positon(x,y);
}

void Text::set_color(COLORREF color)
{
    _color = color;
}

void Text::set_positon(int x, int y)
{
    _x = x;
    _y = y;
}

void Text::set_enable(bool enable)
{
    _enable = enable;
}

void Text::print()
{
    if (true)
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
    
        game_framework::CTextDraw::ChangeFontLog(pDC, _size, "Determination Mono Web", _color, _weight);
    
        game_framework::CTextDraw::Print(pDC, _x, _y, _str);
        game_framework::CDDraw::ReleaseBackCDC();
    }
}
