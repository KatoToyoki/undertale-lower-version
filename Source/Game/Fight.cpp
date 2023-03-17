#include "stdafx.h"
#include "Fight.h"

void Fight::load_img()
{
    fightScope.LoadBitmapByString({"resources/fight_scope.bmp"});
    fightScope.SetTopLeft(356,583);
    
    fightBar.LoadBitmapByString({"resources/fight_bar.bmp"});
    fightBar.SetTopLeft(240,593);
}

void Fight::show_fight_img()
{
    fightScope.ShowBitmap();
    fightBar.ShowBitmap();
}

void Fight::set_fight_img_enable(bool enable)
{
    _enable=enable;
}

int Fight::attack()
{
    return 0;
}

void Fight::MoveingBar()
{
    if(fightBar.GetLeft()<1560){
        fightBar.SetTopLeft(fightBar.GetLeft()+14,590);
    }
}

void Fight::ToStop(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_RETURN)
    {
        _isBarStop=true;
    }
}

