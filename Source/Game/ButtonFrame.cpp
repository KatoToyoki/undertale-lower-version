#include "stdafx.h"
#include "ButtonFrame.h"

ButtonFrame::ButtonFrame()
{
    _fight.LoadBitmapByString({
        "resources/fight_off.bmp",
        "resources/fight_on.bmp",
        "resources/fight_selected.bmp",
    });
    _fight.SetTopLeft(20,700);
    _act.LoadBitmapByString({
        "resources/act_off.bmp",
        "resources/act_on.bmp",
        "resources/act_selected.bmp",
    });
    _act.SetTopLeft(320,700);
    _item.LoadBitmapByString({
        "resources/item_off.bmp",
        "resources/item_on.bmp",
        "resources/item_selected.bmp",
    });
    _item.SetTopLeft(620,700);
    _mercy.LoadBitmapByString({
        "resources/mercy_off.bmp",
        "resources/mercy_on.bmp",
        "resources/mercy_selected.bmp",
    });
    _mercy.SetTopLeft(920,700);
}

void ButtonFrame::changeState(game_framework::CMovingBitmap Off,game_framework::CMovingBitmap On,int command)
{
    Off.SetFrameIndexOfBitmap(toOff);
    switch (command)
    {
    case toLeft:
        _current_selection+=toLeft;
        break;
    case toRight:
        _current_selection+=toRight;
        break;    
    }
    On.SetFrameIndexOfBitmap(toOn);
}


void ButtonFrame::choose_update(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_LEFT)
    {
        switch (_current_selection)
        {
        case act:
            changeState(_act,_fight,toLeft);
            break;
        case item:
            changeState(_item,_act,toLeft);
            break;
        case mercy:
            changeState(_mercy,_item,toLeft);
            break;
        }
    }
    else if(nChar==VK_RIGHT)
    {
        switch (_current_selection)
        {
        case fight:
            changeState(_fight,_act,toRight);
            break;
        case act:
            changeState(_act,_item,toRight);
            break;
        case item:
            changeState(_item,_mercy,toRight);
            break;
        }
    }
}

void ButtonFrame::all_button_off() {
    _fight.SetFrameIndexOfBitmap(toOff);
    _act.SetFrameIndexOfBitmap(toOff);
    _item.SetFrameIndexOfBitmap(toOff);
    _mercy.SetFrameIndexOfBitmap(toOff);
}

int ButtonFrame::get_current_selection() { 
    return _current_selection; 
}


void ButtonFrame::show_button() {
    _fight.SetFrameIndexOfBitmap(toOn);
    _act.SetFrameIndexOfBitmap(toOff);
    _item.SetFrameIndexOfBitmap(toOff);
    _mercy.SetFrameIndexOfBitmap(toOff);
}
