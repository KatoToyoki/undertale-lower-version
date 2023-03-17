#include "stdafx.h"
#include "ButtonFrame.h"

int ButtonFrame::get_current_selection()
{
    return _current_selection;
}

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
}

void ButtonFrame::SetInit()
{
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
    else if(nChar==VK_RETURN)
    {
        target=selected;
        isChange=true;
    }
    // press "esc" to test if all off is okay, it's a temp test
    else if(nChar==VK_ESCAPE)
    {
        target=allOff;
        isChange=true;
    }
}

bool ButtonFrame::GetIsChange()
{
    return isChange;
}

void ButtonFrame::ChangeState()
{
    if(target==selected)
    {
        _buttons[_current_selection].SetFrameIndexOfBitmap(selected);
        return;
    }
    // press "esc" to test if all off is okay, it's a temp test
    else if(target==allOff)
    {
        for(int i=0;i<4;i++)
        {
            _buttons[i].SetFrameIndexOfBitmap(toOff);
        }
        return;
    }
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOff);
    _current_selection+=target; 
    _buttons[_current_selection].SetFrameIndexOfBitmap(toOn);
    isChange=false;
}

void ButtonFrame::GetInActivity()
{
    _buttons[_current_selection].SetFrameIndexOfBitmap(selected);
}

void ButtonFrame::all_button_off() {
    _buttons[fight].SetFrameIndexOfBitmap(toOff);
    _buttons[act].SetFrameIndexOfBitmap(toOff);
    _buttons[item].SetFrameIndexOfBitmap(toOff);
    _buttons[mercy].SetFrameIndexOfBitmap(toOff);
}