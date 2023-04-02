#pragma once
#include "acts.h"
#include "monster_frame.h"
#include "../Library/gamecore.h"

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
    void set_img();
    void show_img();
    int generate_random_num(int min, int max);
/// act
    GameText get_act_after_game_text();
    void set_act_init(int current_selection);
    void set_act_game_text_enable(bool enable);
    
    void act_after_stage_control_updata(UINT nChar, int *stage);

    int get_now_act_after_index();
    int get_now_act_after_text_len();
/// monster frame
    GameText get_monster_frame_game_text();
    
    void set_monster_frame_init(int current_selection);
    void set_monster_frame_game_text_enable(bool enable);
    
    void monster_frame_stage_control_updata(UINT nChar, int *stage,MonsterFrame *monster_frame);

    int get_now_monster_frame_after_index();
    int get_now_monster_frame_after_text_len();
    int get_now_monster_frame_mode();

    MonsterText get_random_game_text(std::string name);
    
    void set_monster_frame();
    Acts acts;
    vector<MonsterText> _monster_text_vector;
///
private:
    bool _act_after_enable = false;
    bool _monster_frame_enable = false;
    int act_times = 0;
    int monster_times = 0;
    int _current_selection;
    int *_stege;
    MonsterFrame *_monster_frame;
    
    void set_acts();

    game_framework::CMovingBitmap enemy_img;
    
};
