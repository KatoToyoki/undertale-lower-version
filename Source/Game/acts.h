#pragma once
#include "game_text.h"

struct Act
{
    std::string name;
};

class Acts
{
public:
    Acts(vector<Act> act_vector ={});
    
    GameText get_act_name_list();
    vector<Act> get_act_list();
    Act* get_act_by_index(int index);

private:
    vector<Act> _act_vector;
};
