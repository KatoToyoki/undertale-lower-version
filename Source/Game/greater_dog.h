#pragma once
#include "enemy.h"
#include "GreaterDogRound.h"
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
    void set_act_text_updata() override;
    void act_choose_count(UINT nChar,int button_current) override;
    void set_monster_frame() override;
    void set_next_round_text_updata() override;

    std::vector<std::vector<std::string>> get_random_text(std::string name) override;
    frame_command get_monster_battle_mode() override;
    void set_fight() override;//if some thing happend hit need to set
    void fight_open(Move* heart, Character* charactor) override;
    bool get_fight_end() override;
    void init_barrage_data() override;
    void show_barrage(Move* heart, Character* charactor, int stage) override;
    
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

    game_framework::CMovingBitmap enemy_img_close;
    GreaterDogRound greater_dog_round;
};
