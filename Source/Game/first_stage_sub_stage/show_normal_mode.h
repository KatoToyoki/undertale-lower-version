#pragma once

#include "../ButtonFrame.h"
#include "../user_frame.h"
#include "../sub_stage.h"

class ShowNormalMode : public SubStage
{
public:
    void init(UserFrame *user_frame,
        ButtonFrame *button_frame);
    void show_monster_text();
    void open_chooes_updata();

    void choose_fight_taget();
    void choose_fight();
    void choose_act_target();
    void choose_act();
    void choose_item();
    void cooose_mercy();
    // void 

    void end();

    UserFrame *_user_frame;
    ButtonFrame *_button_frame;
};
