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
    HP.SetTopLeft(618,_enemy->fight_bar_positon.y);

    HPminus.LoadBitmapByString({"resources/hp_bar_minushp.bmp"});
    HPminus.SetTopLeft(1300,_enemy->fight_bar_positon.y);
    
    HPFrame.LoadBitmapByString({"resources/hp_bar_frame.bmp"}, RGB(255, 255, 255));
    HPFrame.SetTopLeft(618,_enemy->fight_bar_positon.y);

    greenLineRight.LoadBitmapByString({"resources/green_line_right.bmp"}, RGB(255, 255, 255));
    greenLineRight.SetTopLeft(1185,20);

    attack_red.LoadBitmapByString({"resources/attack_0.bmp",
"resources/attack_1.bmp",
    "resources/attack_2.bmp",
    "resources/attack_3.bmp",
    "resources/attack_4.bmp",
    "resources/attack_5.bmp",
    "resources/attack_6.bmp"
        }
    ,RGB(0,0,0));
	attack_red.SetTopLeft(_enemy->red_attck_positon.x,_enemy->red_attck_positon.y);
	attack_red.SetAnimation(150,false);
}
void Fight::set_monster(Enemy* enemy)
{
    _enemy = enemy;
}

void Fight::show_fight_img()
{
    if (_enable)
    {
        fightScope.ShowBitmap();
        fightBar.ShowBitmap();
    }
    else if (!_enable)
    {
        _isBarStop = false;
        _isAttack = false;
        _isHPBarStop = false;
        _isMiss=false;
        minusHP ="";
        fightBarthisRound=0;
        attackThisRound=0;
        fightBar.SetTopLeft(240,593);
        fightScope.UnshowBitmap();
        fightBar.UnshowBitmap();
    }
    
    if((_isAttack || _isMiss) && _enable)
    {
        if(attackThisRound==1)
        {
            attack();
        }

        MovingHPBar();
        
        if(GetDurationMinusHP()>0){
            MinusBG();
            RevealMinusHP();
            ShowHPBar();
        }
        else if(GetDurationMinusHP()==0){
            ResetDurationMinusHP();
            ResetMinusHP();
            ResetIsAttack();
            ResetIsMiss();
            UnshowHPBar();
        }
        if (_isAttack)
        {
            attack_red.ShowBitmap();
            _enemy->set_enemy_img_init_or_damege(damege);
            _enemy->set_fight();
        }
    }
    else if((attackThisRound>0 || fightBarthisRound>0) && _enable)
    {
        _enable=false;
    }
}

void Fight::ResetIsMiss()
{
    _isMiss=false;
}

int Fight::Minus(double range)
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

    return damage;
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
    attackThisRound+=1;
}

void Fight::DetectMissCondition()
{
    if(fightBar.GetLeft()>=theEnd || fightBar.GetLeft()<=theStart)
    {
        _isAttack=false;
        _isMiss=true;
        fightBarthisRound+=1;
        minusHP="MISS";
    }
}

void Fight::MovingBar()
{
    if (_enable && fightBarthisRound==0)
    {
        if(fightBar.GetLeft()<1560 && _isBarStop==false ){
            fightBar.SetTopLeft(fightBar.GetLeft()+16,590);
        }
        else
        {
            DetectMissCondition();
        }
    }
}

void Fight::ToStop(UINT nChar)
{
    if((nChar==VK_RETURN || nChar == 0x5A) && _enable)
    {
        _isBarStop=true;
        _isAttack=true;
        attackThisRound+=1;
        DetectMissCondition();
    }
}

bool Fight::GetIsMiss()
{
    return _isMiss;
}

void Fight::RevealMinusHP()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 40, "UNDERTALE ATTACK FONT (REVERSED)", RGB(255, 0, 0), 800);
    game_framework::CTextDraw::Print(pDC, 860, _enemy->fight_bar_positon.y-70, minusHP);
    game_framework::CDDraw::ReleaseBackCDC();
    if(durationMinusHP!=0)
    {
        durationMinusHP-=1;
    }
}

void Fight::MinusBG()
{
    CDC *pDC = game_framework::CDDraw::GetBackCDC();
    game_framework::CTextDraw::ChangeFontLog(pDC, 30, "UNDERTALE ATTACK FONT (REVERSED)", RGB(0, 255, 0), 800);
    game_framework::CTextDraw::Print(pDC, 870, _enemy->fight_bar_positon.y-60, minusHP);
    game_framework::CDDraw::ReleaseBackCDC();
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
        //374 ori
        HPminus.SetTopLeft(HPminus.GetLeft()-5,_enemy->fight_bar_positon.y);
    }
    else if(HPminus.GetLeft()-4<=minusPosition)
    {
        HPminus.SetTopLeft(minusPosition,_enemy->fight_bar_positon.y);
        _isHPBarStop=true;
    }
}

void Fight::UnshowHPBar()
{
    HP.UnshowBitmap();
    HPminus.UnshowBitmap();
    HPFrame.UnshowBitmap();
}