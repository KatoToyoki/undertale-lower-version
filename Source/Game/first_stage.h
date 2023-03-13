#pragma once

#include "SubStage.h"
class FirstStage
{
public:
    SubStage show_menu;
    SubStage show_normal_mode;
    SubStage show_choose_result;
    SubStage show_battle_mode;

private:
    bool isMenu;
    
};
