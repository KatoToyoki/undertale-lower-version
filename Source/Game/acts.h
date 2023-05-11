#pragma once
#include "game_text.h"

class Acts
{
public:
    Acts(vector<string> act_vector ={});
    
    GameText get_act_name_list();
    vector<string> get_act_list();
    string* get_act_by_index(int index);

private:
    vector<string> _act_vector;
};
