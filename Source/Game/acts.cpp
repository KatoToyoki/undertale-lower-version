#include "stdafx.h"
#include "acts.h"

Acts::Acts(vector<Act> act_vector)
{
    _act_vector = act_vector;
}

GameText Acts::get_act_name_list()
{
    vector<Text> text_vector = {};
    for (Act act : _act_vector)
    {
        Text text(60,act.name,RGB(255,255,255),600,0,0);
        text_vector.push_back(text);
    }
    GameText data(text_vector, act_item_mode);
    return data;
}

vector<Act> Acts::get_act_list()
{
    return _act_vector;
}

Act* Acts::get_act_by_index(int index)
{
    return &_act_vector[index];
}



