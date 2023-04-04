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
    GameText get_monster_name() { return  monster_name; }

    void updata_hp_bar_by_hp();
    void set_enemy_targe_choose_hp_bar(bool enable);
    void show_enemy_targe_choose_hp_bar();
/// act
    GameText get_act_after_game_text();
    void set_act_init(int current_selection);
    void set_act_game_text_enable(bool enable);
    
    void act_after_stage_control_updata(UINT nChar, int *stage);

    int get_now_act_after_index();
    int get_now_act_after_text_len();
/// next_round
    GameText get_next_round_game_text();
    
    int get_next_round_index();
    int get_next_round_text_len();
    
/// monster frame
    GameText get_monster_frame_game_text();
    
    void set_monster_frame_init(int current_selection);
    void set_monster_frame_game_text_enable(bool enable);
    
    void monster_frame_stage_control_updata(UINT nChar, int *stage,MonsterFrame *monster_frame);

    int get_now_monster_frame_after_index();
    int get_now_monster_frame_after_text_len();
    int get_now_monster_frame_mode();

    MonsterText get_random_game_text(std::string name);

    
    Acts acts;
    vector<MonsterText> _monster_text_vector;
    int hp = 100;
    game_framework::CMovingBitmap enemy_barrage;
///
private:
    bool _act_after_enable = false;
    bool _monster_frame_enable = false;
    bool _choose_targe_hp_bar_enable = false;
    int act_times = 0;
    int monster_times = 0;
    int _current_selection =0;
    int *_stege;
    MonsterFrame *_monster_frame;
    GameText monster_name;
    
    void set_acts();
    void set_monster_frame();
    void set_next_round_text();

    int hp_max = 100;
    int hp_bar_x = 884;
    int hp_bar_y = 630;

    game_framework::CMovingBitmap enemy_img;
    game_framework::CMovingBitmap enemy_targe_choose_hp;
    game_framework::CMovingBitmap enemy_targe_choose_hp_red;
    game_framework::CMovingBitmap enemy_targe_choose_hp_black;
    
    

    ///可能新增一堆 控制顯示字的enable或判斷之類的??
};
