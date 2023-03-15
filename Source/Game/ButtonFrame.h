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
    game_framework::CMovingBitmap _fight, _act, _item, _mercy; // [0] off [1] on
    void changeState(game_framework::CMovingBitmap Off,game_framework::CMovingBitmap On, int command);

public:
    // load the images
    ButtonFrame();

    void choose_update(UINT nChar, UINT nRepCnt, UINT nFlags);

    void all_button_off();

    int get_current_selection();

    void show_button();
};
