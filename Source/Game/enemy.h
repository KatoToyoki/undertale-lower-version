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
    damege,
    end_img
};

enum monster_frame_stage
{
    BEFORE_BATTLE,
    AFTER_BATTLE
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
    virtual frame_command_c get_monster_battle_mode() = 0;

    void updata_hp_bar_by_hp();
    void set_enemy_targe_choose_hp_bar(bool enable);
    void show_enemy_targe_choose_hp_bar();
    void set_enemy_img_init_or_damege(int index);

    GameText set_vector_vector_to_game_text(std::vector<std::vector<std::string>> text,int times,mode mode = talk_mode);

    void set_enemy_shark_time(float time);
    void enemy_shark();
    
/// mercy
    GameText get_mercy_game_text() { return mercy_text;}
    GameText get_mercy_win_game_text() { return mercy_win_text;}
    void check_change_mercy_name_to_yellow_by_is_mercy();
    void set_mercy(bool enable) { _is_mercy = enable; }
    bool is_mercy() {return _is_mercy ;}
    
/// barrage
    virtual void set_barrage() {}
    void set_barrage_enable(bool enable);
    virtual void show_barrage(Move *heart, Character *charactor, int stage) = 0;
    Barrage get_barrage();
/// act
    GameText get_act_after_game_text();
    void set_act_init(int current_selection);
    void set_act_game_text_enable(bool enable);
    
    void act_after_stage_control_updata(UINT nChar);
    virtual void act_choose_count(int button_current) = 0;
    
    virtual void set_act_text_updata() = 0;

/// next_round
    //回傳set_next_round_text_updata指定的東西給userframe
    GameText get_next_round_game_text();
    //設定下回合在什麼狀態下 會顯示怎麼字 隨時讀取
    virtual void set_next_round_text_updata() = 0;
    
/// monster frame
    //傳出monster_frame需要的game_text 給monster_frame印出(SHOW_MONSTER_FRAME_STOP用)
    GameText get_monster_frame_game_text(monster_frame_stage stage);
    //用於傳入monster_frame_mode (auto/enter/pass) 給 monster_frame印出
    int get_now_monster_frame_mode(monster_frame_stage stage);
    
    void check_pass(monster_frame_stage stage);
    //初始化monster_times(文本enter次數) 跟 讀隨機台詞的地方
    void set_monster_frame_init();
    //在move會一直輸入 false 直到 需要使用的時候呼叫傳入true
    void set_monster_frame_game_text_enable(bool enable);
    //放在onkeydown控制stage停下 依照monster_times印出文本 
    void monster_frame_stage_control_updata(UINT nChar, MonsterFrame *monster_frame,int stage);
    //設定讀取戰鬥前(BEFORE BATTLE)的monster_frame會印出甚麼字
    //在此處指定monster_frame_game_text/monster_cost_round/monster_frame_mode
    //東西會透過 get_monster_frame_game_text跟 get_now_monster_frame_mode會透過給monster_frame
    virtual void set_monster_frame_before() { monster_frame_mode_before_battle = pass_talk; }
    //設定讀取戰鬥後(AFTER BATTLE)的monster_frame會印出甚麼字
    //在此處指定monster_frame_game_text/monster_cost_round/monster_frame_mode
    //東西會透過 get_monster_frame_game_text跟 get_now_monster_frame_mode會透過給monster_frame
    virtual void set_monster_frame_after() { monster_frame_mode_after_battle = pass_talk; }
//
    virtual void set_fight() {} //fight打到怪會呼叫 如果有要判斷打到怪時 會做出甚麼寫在這裡
    //game_manager choose_mercy_after call  功用是如果怪物被mercy會做什麼變化之類的
    virtual void set_mercy() {} //如果有要判斷mercy 會做出甚麼寫在這裡
    virtual void fight_open(Move *heart, Character *charactor) = 0; 
    virtual bool get_fight_end() = 0;
    void set_battle_timer(int time) {battel_mode_timer = time;}
    virtual void init_barrage_data() {}
    

    Acts acts;
    int hp = 100;
    Coordinate red_attck_positon;
    Coordinate fight_bar_positon;
    
    bool _monster_frame_enable = false;
    bool stage_stop = false;
    bool _is_pass_stage = false;
protected:
    
    int battel_mode_timer = 0;
    bool end_fight = false;
    bool _act_after_enable = false;
    bool _choose_targe_hp_bar_enable = false;
    bool _barrage_enable = false;
    bool _is_mercy = false;
    bool _is_gameover = false;
    bool _is_init = true;
    int act_times = 0;
    int monster_times_before =0;
    int monster_times_after =0;
    int _current_selection =0;
    float shark_time = 0;

    MonsterFrame *_monster_frame;
    GameText monster_name;
    GameText mercy_text;
    GameText mercy_win_text;
    Barrage barrage;
    
    virtual void set_acts() = 0;
    virtual void check_mercy() = 0;

    int hp_max = 100;
    int hp_bar_x = 884;
    int hp_bar_y = 630;
    int enemy_x;
    int enemy_y;

    game_framework::CMovingBitmap enemy_img;
    game_framework::CMovingBitmap enemy_last;
    game_framework::CMovingBitmap enemy_img_init;
    game_framework::CMovingBitmap enemy_img_damege;
    game_framework::CMovingBitmap enemy_img_end;
    game_framework::CMovingBitmap enemy_img_end_effc;
    game_framework::CMovingBitmap enemy_targe_choose_hp;
    game_framework::CMovingBitmap enemy_targe_choose_hp_red;
    game_framework::CMovingBitmap enemy_targe_choose_hp_black;
    game_framework::CMovingBitmap monster_frame_img;
    
    game_framework::CMovingBitmap enemy_barrage;
    
    TextContent text_content;
	GameText act_after;
	GameText act_next_round;
    int cost_round;
    
	GameText monster_frame_game_text_before_battle;
    monster_frame_mode monster_frame_mode_before_battle;
    std::vector<std::vector<std::string>> monster_text;
    int monster_cost_round_before;
    
	GameText monster_frame_game_text_after_battle;
    monster_frame_mode monster_frame_mode_after_battle;
    int monster_cost_round_after;

    std::vector<std::vector<std::string>> next_round_text = {{}};
};
