#include "stdafx.h"
#include "Fight.h"
#include <string>

#include "../Library/audio.h"

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

    if(minusText.size()>0)
    {
        return;
    }
    
   for(int i=0;i<4;i++)
   {
       game_framework::CMovingBitmap temp;
       temp.LoadBitmapByString(
        {"resources/0.bmp",
        "resources/1.bmp",
        "resources/2.bmp",
        "resources/3.bmp",
        "resources/4.bmp",
        "resources/5.bmp",
        "resources/6.bmp",
        "resources/7.bmp",
            "resources/8.bmp",
            "resources/9.bmp",
        "resources/miss.bmp"
        },RGB(255,255,255));
       minusText.push_back(temp);
   }
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
            ShowHPBar();
            RevealMinusText();
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

    monsterHP = damage > monsterHP ? 0 : monsterHP-damage;
    minusPosition = minusPosition-displacement<610 ? 610 : minusPosition-displacement;
    minusHP=std::to_string(damage);

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
        fightBar.GetLeft()<1560 && _isBarStop==false ? fightBar.SetTopLeft(fightBar.GetLeft()+16,590) : DetectMissCondition();
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
        if (attackThisRound == 1 && !_isMiss)
        {
            game_framework::CAudio::Instance() -> Play(7);
            _enemy->set_enemy_shark_time(15);
        }
    }
}

bool Fight::GetIsMiss()
{
    return _isMiss;
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

void Fight::RevealMinusText()
{
    int times = minusHP.length();
    int startPoint = (1920-68*times)/2;
    if(minusHP=="MISS")
    {
        minusText[0].SetFrameIndexOfBitmap(10);
        minusText[0].SetTopLeft(805,_enemy->fight_bar_positon.y-80);
        minusText[0].ShowBitmap();
    }
    else
    {
        for(int i=0;i<times;i++)
        {
            minusText[i].SetFrameIndexOfBitmap(minusHP[i]-'0');
            minusText[i].SetTopLeft(startPoint+68*i,_enemy->fight_bar_positon.y-70);
            minusText[i].ShowBitmap();
        }
    }

    if(durationMinusHP!=0)
    {
        durationMinusHP-=1;
    }
}