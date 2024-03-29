#pragma once

#include "../Library/gameutil.h"
#include "text.h"
class Menu
{
public:
    Menu() = default;
    void init() { isMenu =true; current_stage =1;};
    
    void load_img_set_postion();
    void count_time(long int current_counter,int lev);

    void WholeMenu();
    void MenuState();
    void ShowMenuImg();
    void MenuOff();
    void choose(UINT nChar);
    bool get_menu();
    bool GetIsTutorial();
    int get_current_stage() {return current_stage;}
    
    game_framework::CMovingBitmap menuTop, menuBottom, tutorial;
private:
    Text stage1,stage2,stage3,LV_text,mouse,dog,town;
    Text* save_point;
    int current_stage = 1;
    bool isMenu = true;
    bool isTutorial = false;
    string hour;
    string min;
    int level = 1;
};
