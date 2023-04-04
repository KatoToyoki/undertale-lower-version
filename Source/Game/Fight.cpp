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

void Fight::set_fight_enable(bool enable)
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

    greenLineRight.LoadBitmapByString({"resources/green_line_right.bmp"}, RGB(255, 255, 255));
    greenLineRight.SetTopLeft(1185,20);
}

void Fight::show_fight_img()
{
    if (_enable)
    {
        fightScope.ShowBitmap();
        fightBar.ShowBitmap();
        Test1();
        Test2();
        Test3();
        Test4();
        Test5();
        
    }
    else if (!_enable)
    {
        _isBarStop = false;
        _isAttack = false;
        _isHPBarStop = false;
        minusHP ="";
        attackCount = 0;
        fightBar.SetTopLeft(240,593);
        fightScope.UnshowBitmap();
        fightBar.UnshowBitmap();

        t=0;
        
    }
    
    if((_isAttack==true || IfMiss()==true) && _enable)
    {
        if(t==1)
        {
            attack();
            
        }
        MovingHPBar();
        
        if(GetDurationMinusHP()>0 && GetAttackCount()<=1){
            RevealMinusHP();
            ShowHPBar();
        }
        else if(GetDurationMinusHP()==0){
            ResetDurationMinusHP();
            ResetMinusHP();
            ResetIsAttack();
            UnshowHPBar();
            
        }
        
    }
    else if(IfMiss()==true && _enable)
    {
        if(GetDurationMinusHP()>0)
        {
            RevealMinusHP();
        }
        
    }
    
}

void Fight::Minus(double range)
{
    
    int damage=(int)(test*range);
    int displacement=(int)(MPF*range);
    if(damage>monsterHP)
    {
        monsterHP=0;
    }
    else
    {
        monsterHP-=damage;
    }

    if(minusPosition-displacement<610)
    {
        minusPosition=610;
    }
    else
    {
        minusPosition-=displacement;
    }
    
    minusHP="-"+(std::to_string(damage));
}


void Fight::attack()
{
    
    if((fightBar.GetLeft()>=theStart && fightBar.GetLeft()<thirdFront) || (fightBar.GetLeft()>=thirdBehind && fightBar.GetLeft()<theEnd))
    {
        Minus(0.15);
    }
    else if((fightBar.GetLeft()>=thirdFront && fightBar.GetLeft()<secondFront) || (fightBar.GetLeft()>=secondBehind && fightBar.GetLeft()<thirdBehind))
    {
        Minus(0.18);
    }
    else if((fightBar.GetLeft()>=secondFront && fightBar.GetLeft()<firstFront) || (fightBar.GetLeft()>=firstBehind && fightBar.GetLeft()<secondBehind))
    {
        Minus(0.21);
    }
    else if(fightBar.GetLeft()>=firstFront && fightBar.GetLeft()<firstBehind)
    {
        Minus(0.24);
    }
    
    MovingHPBar();
    t+=1;
}

void Fight::MovingBar()
{
    if (_enable)
    {
        if(fightBar.GetLeft()<1560 && _isBarStop==false){
            fightBar.SetTopLeft(fightBar.GetLeft()+16,590);
            attackCount=0;
        }
    }
}

void Fight::ToStop(UINT nChar)
{
    if(nChar==VK_RETURN && _enable)
    {
        _isBarStop=true;
        _isAttack=true;
        attackCount+=1;
        t+=1;
    }
}

bool Fight::IfMiss()
{
    return (fightBar.GetLeft()>=1520);
}

void Fight::RevealMinusHP()
{
    if(minusHP=="")
    {
        minusHP="MISS";
        attackCount=1;
    }
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "Determination Mono Web", RGB(255, 255, 255), 800);
    game_framework::CTextDraw::Print(pDC, 900, 300, minusHP);
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
    greenLineRight.ShowBitmap();
}

void Fight::MovingHPBar()
{
    if(HPminus.GetLeft()-10>minusPosition && _isHPBarStop==false){
        HPminus.SetTopLeft(HPminus.GetLeft()-5,374);
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

void Fight::Test1()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 0, "minusHP "+to_string(monsterHP));
    game_framework::CDDraw::ReleaseBackCDC();
}

void Fight::Test2()
{
    std::string b=to_string(fightBar.GetLeft());
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 50, "fightbar left "+b);
    game_framework::CDDraw::ReleaseBackCDC();
}

void Fight::Test3()
{
    //std::string a=to_string(monsterHP);

    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 90, "minusPosition "+to_string(minusPosition));
    game_framework::CDDraw::ReleaseBackCDC();
}

void Fight::Test4()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 140, "attackCount "+to_string(attackCount));
    game_framework::CDDraw::ReleaseBackCDC();
}

void Fight::Test5()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 200, "fightbar position"+to_string(fightBar.GetLeft()));
    game_framework::CDDraw::ReleaseBackCDC();
}

void Fight::Test6()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
    game_framework::CTextDraw::Print(pDC, 0, 250, "minusHP "+minusHP);
    game_framework::CDDraw::ReleaseBackCDC();
}