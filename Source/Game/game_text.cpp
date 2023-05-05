#include "stdafx.h"
#include "game_text.h"

GameText::GameText(std::vector<Text> data,mode mode_command)
{
    int i=0;
    _mode = mode_command;
    for (Text &text : data)
    {
        if (mode_command == act_item_mode)
        {
            text.set_positon(460+((i%2)*590),601 + ((i/2)*72) );
        }
        if (mode_command == talk_mode)
        {
            text.set_positon(352,605 + ((i%3)*72) );
        }
        if (mode_command == target_mode)
        {
            text.set_positon(460,601 + ((i%3)*72) );
        }
        if (mode_command == monster_mode)
        {
            text.set_positon(1234,333 + (i%4)*50 );
        }
        i+=1;
            
    }
    _data = data;
}

void GameText::set_enable(bool enable)
{
    _enable = enable;
    for (Text text : _data)
    {
        text.set_enable(_enable);
    }
}

void GameText::print_vector()
{
    if (_enable)
    {
        for (Text text : _data)
        {
            text.print();
        }
    }
}

void GameText::print()
{
    print_vector(); 
}

int GameText::get_vector_len()
{
    return _data.size();
}

int GameText::get_positon_x(int index)
{
    return _data[index]._x;
}

int GameText::get_positon_y(int index)
{
    return _data[index]._y;
}
