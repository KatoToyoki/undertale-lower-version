#pragma once

#include "../Library/gameutil.h"
#include "text.h"
class Menu
{
public:
    Menu() = default;
    
    void load_img_set_postion();

    void WholeMenu();
    void MenuState();
    void ShowMenuImg();
    void MenuOff();
    void choose(UINT nChar);
    bool get_menu();
    
    game_framework::CMovingBitmap menuTop, menuBottom;
private:
    Text stage1,stage2,stage3,LV_text,save_point;
    int current_stage = 1;
    bool isMenu = true;
};
