#pragma once
#include "acts.h"
#include "barrage.h"
#include "enemy.h"
#include "monster_frame.h"
#include "../Library/gamecore.h"

enum migosp_act_selection
{
    CHECK_M,
    TALK_M,
};


class Migosp : public Enemy
{
public:
    Migosp();
    void set_img() override;
    void set_hp_img() override;
    void set_barrage() override;
    void set_acts() override;
    void set_act_text_updata() override;
    void act_choose_count(int button_current) override;
    void set_monster_frame_before() override;
    void set_next_round_text_updata() override;

    frame_command_c get_monster_battle_mode() override ;
    
    void check_mercy() override;
    void fight_open(Move* heart, Character* charactor) override;
    bool get_fight_end() override;

    void show_barrage(Move* heart, Character* charactor,int stage) override;

    //test
    // void set_monster_frame_after() override;
};
