#pragma once
#include "enemy.h"

#define TEXXT(content) Text(60, content, RGB(255,255,255), 600, 420, 69)

enum dog_act_selection
{
    check_d,
    pet_d,
    beckon_d,
    play_d,
    ignore_d
};

enum dog_act_pet
{
    before_beckon,
    after_ignore_or_beckon,
    before_play_afb,
    after_play_pet_1_afb,
    after_play_pet_2_afb,
    after_play_pet_plus_afb,
};

enum dog_act_play
{
    not_excited,
    excited,
    after_excited_plus
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
    void act_choose_count(UINT nChar) override;
    void set_act_init(Act* act,int index, vector<int> list,int round);
    void set_dog_init_pet(Act* act,dog_act_pet num);
    void set_dog_init_play(Act* act,dog_act_play num);
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
    bool is_beckon = false;
};
