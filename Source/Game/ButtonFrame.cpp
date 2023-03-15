#include "stdafx.h"
#include "ButtonFrame.h"

void ButtonFrame::LoadSetIMG()
{
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
}

void ButtonFrame::show_button() {
    _fight.SetFrameIndexOfBitmap(toOn);
    _fight.ShowBitmap();
    _act.SetFrameIndexOfBitmap(toOff);
    _act.ShowBitmap();
    _item.SetFrameIndexOfBitmap(toOff);
    _item.ShowBitmap();
    _mercy.SetFrameIndexOfBitmap(toOff);
    _mercy.ShowBitmap();
}