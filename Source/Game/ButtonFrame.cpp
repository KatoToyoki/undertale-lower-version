#include "stdafx.h"
#include "ButtonFrame.h"

void ButtonFrame::LoadSetIMG()
{
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

    _buttons[fight].SetFrameIndexOfBitmap(toOn);
    _buttons[act].SetFrameIndexOfBitmap(toOff);
    _buttons[item].SetFrameIndexOfBitmap(toOff);
    _buttons[mercy].SetFrameIndexOfBitmap(toOff);
}

void ButtonFrame::show_button() {
    _buttons[fight].ShowBitmap();
    _buttons[act].ShowBitmap();
    _buttons[item].ShowBitmap();
    _buttons[mercy].ShowBitmap();
}

void ButtonFrame::changeState()
{
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOff);
    _current_selection+=target; 
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOn);
    show_button();
    isChange=false;
}

int ButtonFrame::getCurrentSelection()
{
    return _current_selection;
}

int ButtonFrame::getTarget()
{
    return target;
}

void ButtonFrame::choose_update(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_LEFT && _current_selection!=fight)
    {
        target=toLeft;
        isChange=true;
    }
    else if(nChar==VK_RIGHT && _current_selection!=mercy)
    {
        target=toRight;
        isChange=true;
    }
}

void ButtonFrame::setCurentSelection(int curr)
{
    _current_selection=curr;
}

bool ButtonFrame::getIsChange()
{
    return isChange;
}


void ButtonFrame::all_button_off() {
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