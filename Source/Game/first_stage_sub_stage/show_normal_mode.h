#pragma once

#include "../userFrame.h"
#include "../SubStage.h"
class ShowNormalMode : public SubStage
{
public:
    void init(UserFrame *user_frame);
    void set_frame();

    void end();

    UserFrame *_user_frame;
    
};
