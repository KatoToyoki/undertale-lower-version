#pragma once
#include "acts.h"
#include "barrage.h"
#include "enemy.h"
#include "monster_frame.h"
#include "../Library/gamecore.h"

enum migosp_act_selection
{
    check_m,
    talk_m,
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
    void act_choose_count(UINT nChar,int button_current) override {}
    void set_monster_frame() override;
    void set_next_round_text_updata() override;

    std::vector<std::vector<std::string>> get_random_text(std::string name) override;
    frame_command get_monster_battle_mode() override { return talk_to_normal_battle; }
    
    void check_mercy() override;
    void fight_open(Move* heart, Character* charactor) override;
    bool get_fight_end() override;

    void show_barrage(Move* heart, Character* charactor,int stage) override;
    
///
private:
};
