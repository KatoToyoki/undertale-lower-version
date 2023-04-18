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
    pet_m
};


class Migosp : public Enemy
{
public:
    Migosp();
    void set_img() override;
    void set_barrage() override;
    void set_acts() override;
    void set_act_init(int current_selection) override;
    void set_monster_frame() override;
    void set_next_round_text() override;

    MonsterText get_random_game_text(std::string name) override;
    int get_next_round_index() override;
    frame_command get_monster_battle_mode() override { return talk_to_normal_battle; }
    
    void check_mercy() override;
    
///
private:
    
    

    ///可能新增一堆 控制顯示字的enable或判斷之類的??
};
