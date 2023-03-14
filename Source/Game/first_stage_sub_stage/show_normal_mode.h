#pragma once

#include "../monster_frame.h"
#include "../user_frame.h"
#include "../sub_stage.h"

class ShowNormalMode : public SubStage
{
public:
    void init(UserFrame *user_frame);
    void show_monster_text();
    void open_chooes_updata();
    
    // void 

    void end();

    UserFrame *_user_frame;
    MonsterFrame monster_frame();
};
