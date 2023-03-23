#pragma once

#include "../ButtonFrame.h"
#include "../monster_frame.h"
#include "../user_frame.h"
#include "../sub_stage.h"

class ShowNormalMode : public SubStage
{
public:
    void init(UserFrame *user_frame,
        ButtonFrame *button_frame,MonsterFrame *monster_frame,Move *heart_test);
    void end();

    void choose_fight_taget();
    void choose_fight();
    void choose_act_target();
    void choose_act();
    void choose_act_after();
    void choose_item();
    void choose_mercy(){};

    UserFrame *_user_frame;
    ButtonFrame *_button_frame;
    MonsterFrame *_monster_frame;
    Move *_heart_test;
};
