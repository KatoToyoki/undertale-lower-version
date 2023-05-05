#pragma once

#include "acts.h"
#include "barrage.h"
#include "monster_frame.h"
#include "TextContent.h"
#include "user_frame.h"

#define TEXXT(content) Text(60, content, RGB(255,255,255), 600, 420, 69)
#define TEXXT_M(content) Text(33, content, RGB(0,0,0), 30, 420, 69)

enum enemy_img_state
{
    init_img,
    damege
};

class Enemy
{
public:
    virtual void set_hp_img() = 0;
    virtual void set_img() = 0;
    bool is_game_over() {return  _is_gameover;}
    void show_img();
    int generate_random_num(int min, int max);
    GameText get_monster_name() { return  monster_name; }
    virtual frame_command get_monster_battle_mode() = 0;

    void updata_hp_bar_by_hp();
    void set_enemy_targe_choose_hp_bar(bool enable);
    void show_enemy_targe_choose_hp_bar();
    void set_enemy_img_init_or_damege(int index);

/// mercy
    GameText get_mercy_game_text() { return mercy_text;}
    GameText get_mercy_win_game_text() { return mercy_win_text;}
    void check_change_mercy_name_to_yellow_by_is_mercy();
    void set_mercy(bool enable) { _is_mercy = enable; }
    bool is_mercy() {return _is_mercy ;}
    
/// barrage
    virtual void set_barrage() = 0;
    void set_barrage_enable(bool enable);
    void show_barrage();
    Barrage get_barrage();
/// act
    GameText get_act_after_game_text();
    void set_act_init(int current_selection);
    void set_act_game_text_enable(bool enable);
    
    void act_after_stage_control_updata(UINT nChar, int *stage);
    virtual void act_choose_count(UINT nChar) = 0;
    
    virtual void set_act_updata() = 0;

/// next_round
    GameText get_next_round_game_text();
    
/// monster frame
    GameText get_monster_frame_game_text();
    
    void set_monster_frame_init();
    void set_monster_frame_game_text_enable(bool enable);
    
    void monster_frame_stage_control_updata(UINT nChar, int *stage,MonsterFrame *monster_frame);

    int get_now_monster_frame_mode();
    virtual void set_monster_frame() = 0;

    virtual std::vector<std::vector<std::string>> get_random_text(std::string name) = 0;

    Acts acts;
    int hp = 100;
    game_framework::CMovingBitmap enemy_barrage;
    
    bool _monster_frame_enable = false;
protected:
    
    bool _act_after_enable = false;
    bool _choose_targe_hp_bar_enable = false;
    bool _barrage_enable = false;
    bool _is_mercy = false;
    bool _is_gameover = false;
    int act_times = 0;
    int monster_times = 0;
    int _current_selection =0;
    int *_stege;
    MonsterFrame *_monster_frame;
    GameText monster_name;
    GameText mercy_text;
    GameText mercy_win_text;
    Barrage barrage;
    
    virtual void set_acts() = 0;
    virtual void check_mercy() = 0;
    virtual void set_next_round_text() = 0;

    int hp_max = 100;
    int hp_bar_x = 884;
    int hp_bar_y = 630;

    game_framework::CMovingBitmap enemy_img;
    game_framework::CMovingBitmap enemy_img_init;
    game_framework::CMovingBitmap enemy_img_damege;
    game_framework::CMovingBitmap enemy_targe_choose_hp;
    game_framework::CMovingBitmap enemy_targe_choose_hp_red;
    game_framework::CMovingBitmap enemy_targe_choose_hp_black;
    
	std::vector<Text> act_text_vector;
	std::vector<Text> next_text_vector;
    std::vector<std::vector<std::string>> act_text;
    std::vector<std::vector<std::string>> next_round_text;
    TextContent text_content;
	GameText act_after;
	GameText act_next_round;
    int cost_round;
    
	std::vector<Text> monster_text_vector;
	GameText monster_frame_game_text;
    std::vector<std::vector<std::string>> monster_text;
    int monster_cost_round;
    monster_frame_mode monster_frame_mode;
    
};
