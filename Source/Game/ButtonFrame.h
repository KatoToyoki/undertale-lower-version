#pragma once
#include "stdafx.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

enum command{toLeft=-1,toRight=1};
enum status { toOff, toOn, selected,allOff };
enum activities { fight, act, item, mercy };

class ButtonFrame {
private:
    // default is fight
    int _current_selection = fight;
    
    // connect with status, to see what to do next
    int target=0;
    
    // be used to see if chageStatue will be execute or not
    bool isChange=false;
    
    // fight, act, item, mercy buttons
    game_framework::CMovingBitmap _buttons[4] ;

    bool _enable = false;

public:
    ButtonFrame()=default;
    ~ButtonFrame()=default;

    // REQUIRED
    // get current selection
    int get_current_selection();
    
    // load and set position of four button images
    void LoadSetIMG();
    
    // to set the default images of each button
    void SetInit();

    // REQUIRED
    // to reveal all the buttons
    void show_button();

    // REQUIRED
    // depending on key in, decide what target is, then do the function on OnShow
    void choose_update(UINT nChar);
    
    // to get private member, isChange
    bool GetIsChange();
    
    // if isChange is true, then change to state depend on target
    void ChangeState();
    
    // when key in is enter, set the image in selected status
    void GetInActivity();

    // REQUIRED
    // set all the buttons off
    void all_button_off();

    void set_updata_enable(bool enable);
};