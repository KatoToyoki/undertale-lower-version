#pragma once

#include "ButtonFrame.h"
#include "Character.h"
#include "Fight.h"
#include "items.h"
#include "monster_frame.h"
#include "user_frame.h"
#include "sub_stage.h"

class GameManager : public SubStage
{
public:
    void updata();
    void init();
    void end();

    void choose_fight_taget();
    void choose_fight();
    void choose_act_target();
    void choose_act();
    void choose_act_after();
    void choose_item();
    void choose_item_after();
    void choose_mercy();
    void choose_mercy_after();

    void monster_frame_no_battle();
    void monster_frame_battle();
    void battle_after_monster_frame();


    void set_heart_mode(HeartMode mode);
    void load_data(UserFrame *user_frame,
        ButtonFrame *button_frame,MonsterFrame *monster_frame,
        Move *heart_test,Fight *game_fight,
        Enemy *enemy, Items *items,
        Character *charactor);

    UserFrame *_user_frame;
    ButtonFrame *_button_frame;
    MonsterFrame *_monster_frame;
    Move *_heart_test;
    Fight *_game_fight;
    Enemy *_enemy;
    Items *_items;
    Character *_charactor;

    int last_act_selection = 0;
};
