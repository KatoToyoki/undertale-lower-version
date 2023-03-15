#pragma once
#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

enum command{toLeft=-1,toRight=1};
enum status { toOff, toOn, selected };
enum activities { fight, act, item, mercy };

class ButtonFrame {
private:
    int _current_selection = fight;
    //int direction;
    game_framework::CMovingBitmap _fight,_act,_item,_mercy ;
    game_framework::CMovingBitmap _buttons[4] ;

    // void changeState(game_framework::CMovingBitmap Off,game_framework::CMovingBitmap On, int command);
    

    
public:
    // load the images
    ButtonFrame()=default;
    void LoadSetIMG();
    void changeState(int direction);
    int getCurrentSelection();
    void setCurentSelection(int curr);
    void show_button();

    void choose_update(UINT nChar, UINT nRepCnt, UINT nFlags);
    //int choose_update(UINT nChar, UINT nRepCnt, UINT nFlags);

    
    void all_button_off();

    int get_current_selection();
};
