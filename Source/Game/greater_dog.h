#pragma once
#include "enemy.h"
#include "TextContent.h"


enum dog_act_selection
{
    check_d,
    pet_d,
    beckon_d,
    play_d,
    ignore_d
};

class GreaterDog : public Enemy
{
public:
    GreaterDog();
    void set_img() override;
    void set_hp_img() override;
    void set_barrage() override;
    void set_acts() override;
    void set_act_init(int current_selection) override;
    void set_act_updata() override;
    void act_choose_count(UINT nChar) override;
    void set_monster_frame() override;
    void set_next_round_text() override;

    MonsterText get_random_game_text(std::string name) override;
    int get_next_round_index() override;
    // frame_command get_monster_battle_mode() override;
    frame_command get_monster_battle_mode() override { return talk_to_long_battle; }
    
    void check_mercy() override;
private:
    int ignore_times = 0;
    int beckon_times = 0;
    int pet_times = 0;
    int play_times = 0;
    int act_times_enter = 0;
    bool is_beckon = false;
    bool is_play_afb = false;//play過在b之後
    bool is_pet_afb = false;//pet過在b之後
    bool is_init = true;

    Barrage dog_b,dog_soul,dog_bark_1,dog_bark_2;

    
};
