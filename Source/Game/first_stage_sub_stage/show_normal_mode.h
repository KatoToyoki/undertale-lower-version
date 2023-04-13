#pragma once

#include "../ButtonFrame.h"
#include "../charactor.h"
#include "../Fight.h"
#include "../items.h"
#include "../migosp.h"
#include "../monster_frame.h"
#include "../user_frame.h"
#include "../sub_stage.h"

class ShowNormalMode : public SubStage
{
public:
    void init(UserFrame *user_frame,
        ButtonFrame *button_frame,MonsterFrame *monster_frame,
        Move *heart_test,Fight *game_fight,
        Migosp *enemy, Items *items,
        Charactor *charactor);
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


    void set_heart_mode(HeartMode mode);

    UserFrame *_user_frame;
    ButtonFrame *_button_frame;
    MonsterFrame *_monster_frame;
    Move *_heart_test;
    Fight *_game_fight;
    Migosp *_enemy;
    Items *_items;
    Charactor *_charactor;

    int last_act_selection = 0;
};
