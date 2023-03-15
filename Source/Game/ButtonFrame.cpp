#include "stdafx.h"
#include "ButtonFrame.h"

void ButtonFrame::LoadSetIMG()
{
    /*
    _fight.LoadBitmapByString({
        "resources/fight_off.bmp",
        "resources/fight_on.bmp",
        "resources/fight_selected.bmp",
    });
    _fight.SetTopLeft(335,917);
    
    _act.LoadBitmapByString({
        "resources/act_off.bmp",
        "resources/act_on.bmp",
        "resources/act_selected.bmp",
    });
    _act.SetTopLeft(665,917);
    
    _item.LoadBitmapByString({
        "resources/item_off.bmp",
        "resources/item_on.bmp",
        "resources/item_selected.bmp",
    });
    _item.SetTopLeft(1000,917);
    
    _mercy.LoadBitmapByString({
        "resources/mercy_off.bmp",
        "resources/mercy_on.bmp",
        "resources/mercy_selected.bmp",
    });
    _mercy.SetTopLeft(1335,917);
    */
    _buttons[fight].LoadBitmapByString({
        "resources/fight_off.bmp",
        "resources/fight_on.bmp",
        "resources/fight_selected.bmp",
    });
    _buttons[fight].SetTopLeft(335,917);
    
    _buttons[act].LoadBitmapByString({
        "resources/act_off.bmp",
        "resources/act_on.bmp",
        "resources/act_selected.bmp",
    });
    _buttons[act].SetTopLeft(665,917);
    
    _buttons[item].LoadBitmapByString({
        "resources/item_off.bmp",
        "resources/item_on.bmp",
        "resources/item_selected.bmp",
    });
    _buttons[item].SetTopLeft(1000,917);
    
    _buttons[mercy].LoadBitmapByString({
        "resources/mercy_off.bmp",
        "resources/mercy_on.bmp",
        "resources/mercy_selected.bmp",
    });
    _buttons[mercy].SetTopLeft(1335,917);
}

void ButtonFrame::show_button() {
    /*
    _fight.SetFrameIndexOfBitmap(toOn);
    _fight.ShowBitmap();
    _act.SetFrameIndexOfBitmap(toOff);
    _act.ShowBitmap();
    _item.SetFrameIndexOfBitmap(toOff);
    _item.ShowBitmap();
    _mercy.SetFrameIndexOfBitmap(toOff);
    _mercy.ShowBitmap();
    */
    _buttons[fight].SetFrameIndexOfBitmap(toOn);
    _buttons[fight].ShowBitmap();
    _buttons[act].SetFrameIndexOfBitmap(toOff);
    _buttons[act].ShowBitmap();
    _buttons[item].SetFrameIndexOfBitmap(toOff);
    _buttons[item].ShowBitmap();
    _buttons[mercy].SetFrameIndexOfBitmap(toOff);
    _buttons[mercy].ShowBitmap();
}
/*
void ButtonFrame::changeState(game_framework::CMovingBitmap Off,game_framework::CMovingBitmap On,int command)
{
    Off.SetFrameIndexOfBitmap(toOff);
    Off.ShowBitmap();
    
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
    On.ShowBitmap();
}
*/
void ButtonFrame::changeState(int direction)
{
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOff);
    _buttons[_current_selection].ShowBitmap();
    _current_selection+=direction;
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOn);
    _buttons[_current_selection].ShowBitmap();
}

int ButtonFrame::getCurrentSelection()
{
    return _current_selection;
}


void ButtonFrame::choose_update(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_LEFT)
    {
        switch (_current_selection)
        {
        case act:
            //changeState(_act,_fight,toLeft);
            //direction=toLeft;
            _current_selection=act*toLeft;
            //return act*toLeft;
            
        case item:
            //changeState(_item,_act,toLeft);
            //direction=toLeft;
            _current_selection=item*toLeft;

            //return item*toLeft;
            
        case mercy:
            //changeState(_mercy,_item,toLeft);
            //direction=toLeft;
            _current_selection=mercy*toLeft;

            //return mercy*toLeft;
        }
    }
    else if(nChar==VK_RIGHT)
    {
        switch (_current_selection)
        {
        case fight:
            //changeState(_fight,_act,toRight);
            //break;
            //direction=toRight;
            _current_selection= fight*toRight;
        case act:
            //changeState(_act,_item,toRight);
            //break;
            //direction=toRight;
            _current_selection= act*toRight;
        case item:
            //changeState(_item,_mercy,toRight);
            //break;
            //direction=toRight;
            _current_selection=item*toRight;
        }
    }
}

void ButtonFrame::setCurentSelection(int curr)
{
    _current_selection=curr;
}


void ButtonFrame::all_button_off() {
    /*
    _fight.SetFrameIndexOfBitmap(toOff);
    _act.SetFrameIndexOfBitmap(toOff);
    _item.SetFrameIndexOfBitmap(toOff);
    _mercy.SetFrameIndexOfBitmap(toOff);

    _fight.ShowBitmap();
    _act.ShowBitmap();
    _item.ShowBitmap();
    _mercy.ShowBitmap();
    */

    _buttons[fight].SetFrameIndexOfBitmap(toOff);
    _buttons[act].SetFrameIndexOfBitmap(toOff);
    _buttons[item].SetFrameIndexOfBitmap(toOff);
    _buttons[mercy].SetFrameIndexOfBitmap(toOff);

    _buttons[fight].ShowBitmap();
    _buttons[act].ShowBitmap();
    _buttons[item].ShowBitmap();
    _buttons[mercy].ShowBitmap();
}

int ButtonFrame::get_current_selection() { 
    return _current_selection; 
}
