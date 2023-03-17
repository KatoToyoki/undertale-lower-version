#pragma once

#include "../Library/gameutil.h"
class Menu
{
public:
    Menu() = default;
    
    void load_img_set_postion();

    void WholeMenu(int current_stage);
    void MenuState(int current_stage);
    void ShowMenuImg();
    void Stage1OFF();
    void Stage2OFF();
    void Stage3OFF();
    void Stage1ON();
    void Stage2ON();
    void Stage3ON();
    void MenuOff();
    
    game_framework::CMovingBitmap menuTop, menuBottom;
};
