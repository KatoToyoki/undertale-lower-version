#include "stdafx.h"
#include "text.h"

#include "mygame.h"

Text::Text(int size, std::string str, COLORREF color, int weight, int x, int y,TEXT_MODE text_mode)
{
    _size = size;
    _str = str;
    _color = color;
    _weight = weight;
    _str_index = 0;
    _text_mode = text_mode;
    set_positon(x,y);
    if (text_mode == TYPE)
    {
        _print_text = "";
        print_over = false;
    }
    else
    {
        _print_text = _str;
        print_over = true;
    }
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

void Text::type_mode()
{
    timer+=1;
    if (_str != _print_text && timer%2 == 0 && _str_index<=(int)_str.length())
    {
        game_framework::CAudio::Instance() -> Play(10+(_str_index%10));
        _print_text+= _str[_str_index];
        _str_index+=1;
    }
    if (_str == _print_text)
    {
        print_over = true;
    }
}

void Text::print()
{
    if (_text_mode == TYPE) type_mode();
    
    CDC *pDC = game_framework::CDDraw::GetBackCDC();

    game_framework::CTextDraw::ChangeFontLog(pDC, _size, "Determination Mono Web", _color, _weight);

    game_framework::CTextDraw::Print(pDC, _x, _y, _print_text);
    game_framework::CDDraw::ReleaseBackCDC();
}

