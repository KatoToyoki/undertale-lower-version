#pragma once
#include "acts.h"

enum migosp_act_selection
{
    check,
    talk,
    pet
};

class Migosp
{
public:
    Migosp();
    
    GameText get_act_after_game_text();
    void set_act_init(int current_selection);
    void set_game_text_enable(bool enable);
    
    void act_after_stage_control_updata(UINT nChar, int *stage);

    int get_now_act_after_index();
    int get_now_act_after_text_len();
    
    Acts acts;

private:
    bool _act_after_enable = false;
    int times = 0;
    int _current_selection;
    int *_stege;
    
    void set_acts();
    
};
