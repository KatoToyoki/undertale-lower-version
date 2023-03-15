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
    game_framework::CMovingBitmap _fight ;
    game_framework::CMovingBitmap _act;
    game_framework::CMovingBitmap _item;
    game_framework::CMovingBitmap _mercy;

public:
    // load the images
    ButtonFrame()=default;
    void LoadSetIMG();

    void show_button();
};
