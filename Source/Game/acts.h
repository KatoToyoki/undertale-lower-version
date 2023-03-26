#pragma once
#include "game_text.h"

struct Act
{
    std::string name;
    GameText act_after;
    GameText act_next_round;
    int index = 0;
    int cost_round = 1;
    vector<int> act_after_len_list;
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
