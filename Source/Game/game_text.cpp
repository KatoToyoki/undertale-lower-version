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
            text.set_positon(465+((i%2)*590),613 + ((i/2)*72) );
        }
        if (mode_command == talk_mode)
        {
            text.set_positon(370,613 + ((i%3)*72) );
        }
        if (mode_command == target_mode)
        {
            text.set_positon(465,613 + ((i%3)*72) );
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

void GameText::set_text_index(int head, int text_len)
{
    print_index = head;
    _text_len = text_len;
}


void GameText::print_text()
{
    for (int i=print_index; i<_text_len+1; i++)
    {
        _data[i].set_positon(370,613 + (((i-print_index)%3)*72) );
        _data[i].print();
    }
}

int GameText::get_vector_len()
{
    return _data.size();
}
