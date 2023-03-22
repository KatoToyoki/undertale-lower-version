#include "stdafx.h"
#include "Fight.h"
#include <string>

bool Fight::GetEnable()
{
    return _enable;
}

bool Fight::GetIsAttack()
{
    return _isAttack;
}

std::string Fight::GetMinusHP()
{
    return minusHP;
}

int Fight::GetAttackCount()
{
    return attackCount;
}

int Fight::GetDurationMinusHP()
{
    return durationMinusHP;
}

void Fight::set_fight_img_enable(bool enable)
{
    _enable=enable;
}

void Fight::ResetDurationMinusHP()
{
    durationMinusHP=100;
}

void Fight::ResetMinusHP()
{
    minusHP="";
}

void Fight::ResetIsAttack()
{
    _isAttack=false;
}

void Fight::load_img()
{
    fightScope.LoadBitmapByString({"resources/fight_scope.bmp"});
    fightScope.SetTopLeft(356,583);
    
    fightBar.LoadBitmapByString({"resources/fight_bar.bmp"});
    fightBar.SetTopLeft(240,593);

    HP.LoadBitmapByString({"resources/hp_bar_hp.bmp"});
    HP.SetTopLeft(618,374);

    HPminus.LoadBitmapByString({"resources/hp_bar_minushp.bmp"});
    HPminus.SetTopLeft(1300,374);
    
    HPFrame.LoadBitmapByString({"resources/hp_bar_frame.bmp"}, RGB(255, 255, 255));
    HPFrame.SetTopLeft(618,374);
}

void Fight::show_fight_img()
{
    fightScope.ShowBitmap();
    fightBar.ShowBitmap();
}

int Fight::attack()
{
    if((fightBar.GetLeft()>=theStart && fightBar.GetLeft()<thirdFront) || (fightBar.GetLeft()>=thirdBehind && fightBar.GetLeft()<theEnd))
    {
        monsterHP-=(int)(test*0.15);
        minusPosition=(int)(1300-(minusPosition*0.15));
        MovingHPBar();
        minusHP="-"+(std::to_string((int)(test*0.15)));
    }
    else if((fightBar.GetLeft()>=thirdFront && fightBar.GetLeft()<secondFront) || (fightBar.GetLeft()>=secondBehind && fightBar.GetLeft()<thirdBehind))
    {
        monsterHP-=(int)(test*0.18);
        minusPosition=(int)(1300-(minusPosition*0.18));
        MovingHPBar();
        minusHP="-"+(std::to_string((int)(test*0.18)));
    }
    else if((fightBar.GetLeft()>=secondFront && fightBar.GetLeft()<firstFront) || (fightBar.GetLeft()>=firstBehind && fightBar.GetLeft()<secondBehind))
    {
        monsterHP-=(int)(test*0.21);
        minusPosition=(int)(1300-(minusPosition*0.21));
        MovingHPBar();
        minusHP="-"+(std::to_string((int)(test*0.21)));
    }
    else if(fightBar.GetLeft()>=firstFront && fightBar.GetLeft()<firstBehind)
    {
        monsterHP-=(int)(test*0.24);
        minusPosition=(int)(1300-(minusPosition*0.24));
        MovingHPBar();
        minusHP="-"+(std::to_string((int)(test*0.24)));
    }
    else if(fightBar.GetLeft()>=firstBehind)
    {
        minusHP="MISS";
        _isAttack=true;
    }
    return 0;
}

void Fight::MovingBar()
{
    if(fightBar.GetLeft()<1560 && _isBarStop==false){
        fightBar.SetTopLeft(fightBar.GetLeft()+16,590);
        attackCount=0;
    }
}

void Fight::ToStop(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_RETURN)
        // minusHP.compare("MISS")==0
        {
        _isBarStop=true;
        _isAttack=true;
        attackCount+=1;
        }
}

bool Fight::IfMiss()
{
    if((minusHP.compare("MISS")==0) || (fightBar.GetLeft()>=1520))
    {
        return true;
    }
    return false;
}

void Fight::RevealMinusHP()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
    game_framework::CTextDraw::Print(pDC, 900, 280, minusHP);
    game_framework::CDDraw::ReleaseBackCDC();
    if(durationMinusHP!=0)
    {
        durationMinusHP-=1;
    }
}

void Fight::ShowHPBar()
{
    HP.ShowBitmap();
    HPminus.ShowBitmap();
    HPFrame.ShowBitmap();
}

void Fight::MovingHPBar()
{
    if(HPminus.GetLeft()-10>minusPosition && _isHPBarStop==false){
        HPminus.SetTopLeft(HPminus.GetLeft()-4,374);
    }
    else if(HPminus.GetLeft()-4<=minusPosition)
    {
        HPminus.SetTopLeft(minusPosition,374);
        _isHPBarStop=true;
    }
}

void Fight::UnshowHPBar()
{
    HP.UnshowBitmap();
    HPminus.UnshowBitmap();
    HPFrame.UnshowBitmap();
    _enable=false;
}

void Fight::EndFight()
{
    fightScope.UnshowBitmap();
    fightBar.UnshowBitmap();
    fightBar.SetTopLeft(240,593);
}