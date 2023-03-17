#include "stdafx.h"
#include "Fight.h"

#include <string>

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
    /*
    if(monsterHP==1000)
    {
        minusHP="WWW";
        return 1;
    }
    */
    if((fightBar.GetLeft()>=theStart && fightBar.GetLeft()<thirdFront) || (fightBar.GetLeft()>=thirdBehind && fightBar.GetLeft()<theEnd))
    {
        monsterHP-=(int)(test*0.15);
        //minusHP="why";
        minusHP=std::to_string((int)(test*0.15));
    }
    else if((fightBar.GetLeft()>=thirdFront && fightBar.GetLeft()<secondFront) || (fightBar.GetLeft()>=secondBehind && fightBar.GetLeft()<thirdBehind))
    {
        monsterHP-=(int)(test*0.18);
        //minusHP="what";
        minusHP=std::to_string((int)(test*0.18));
    }
    else if((fightBar.GetLeft()>=secondFront && fightBar.GetLeft()<firstFront) || (fightBar.GetLeft()>=firstBehind && fightBar.GetLeft()<secondBehind))
    {
        monsterHP-=(int)(test*0.21);
        minusHP=std::to_string((int)(test*0.21));
    }
    else if(fightBar.GetLeft()>=firstFront && fightBar.GetLeft()<firstBehind)
    {
        monsterHP-=(int)(test*0.24);
        minusHP=std::to_string((int)(test*0.24));
    }

    
    return 0;
}

void Fight::MoveingBar()
{
    if(fightBar.GetLeft()<1560 && _isBarStop==false){
        fightBar.SetTopLeft(fightBar.GetLeft()+16,590);
    }
}

void Fight::ToStop(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_RETURN)
    {
        _isBarStop=true;
        _isAttack=true;
    }
}

void Fight::RevealMinusHP()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
    game_framework::CTextDraw::Print(pDC, 500, 320, minusHP);
    game_framework::CDDraw::ReleaseBackCDC();
    minusHP="";
    _isAttack=false;
}

void Fight::TTTT()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
    game_framework::CTextDraw::Print(pDC, 1000, 320, "HP test");
    game_framework::CDDraw::ReleaseBackCDC();
    minusHP="";
}
