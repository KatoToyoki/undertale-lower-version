#pragma once
#include "stdafx.h"

#include "migosp.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

/*
 * range : 431~1540
 * 0.0 - 0.1 - 0.3 - 0.46 - 0.54 - 0.7 - 0.9 - 1.0
 *   0.15%  0.18%  0.21%  0.24% 0.21% 0.18%  0.15%
 *
 *  give enemy attack depends on the fight bar position
 *  this is the fight bar position ranges
 */
enum fightRange
{
    theStart=431,thirdFront=542,secondFront=764,firstFront=940,firstBehind=1028,secondBehind=1204,thirdBehind=1426,theEnd=1520
};

/*
 * it is the temp monster hp, in order to test if minus hp and hp bar works correctly or not
 * it should be CONSISTENT with variable int minsterHP because it is the base
 * every time the attack monster receives is the base * percentage, not current HP * percentage
 */
enum MonsterFull
{
    test=100
};

enum MinusPositionFull
{
    MPF=682 //618+681=1299 = 1300
};

class Fight
{
private:
    // enable is to control the fight flow is willing and ready to do
    bool _enable=false;
    
    // the images of fight range and white fight bar
    game_framework::CMovingBitmap fightScope,fightBar;

    // the attack bar will keep moving if no enter pressed
    // this is the tool to let it GRADUALLY moving
    // after press the enter key, it will stop and do minus hp things
    bool _isBarStop=false;

    // this variable is to control the flow of after press the enter key
    // if _isAttack is true, it will reveal minusHP on the screen and the HP bar will moving
    bool _isAttack=false;

    // the HP bar will keep moving if it don't get the correct x position
    // this is the tool to let it GRADUALLY moving
    bool _isHPBarStop=false;
    
    // the images of HP frame, green HP and black(minus) HP
    game_framework::CMovingBitmap HPFrame,HP,HPminus;

    // this is the transition of int minus HP in order to be displayed on screen
    std::string minusHP="";

    // this is the black(minus) HP initial position.
    int minusPosition=1300;
   
    // temp testing variable, should be CONSISTENT with enum MonsterFull, it is the current hp the monster left
    int monsterHP=100;

    // this is to let items stay on screen for a while, not just quickly disappear
    int durationMinusHP=100;

    // to avoid the green line be covered
    game_framework::CMovingBitmap greenLineRight;

    // for the miss condition
    bool _isMiss=false;

    // to not let attack continue executing
    int attackThisRound=0;

    // to let fight bar move once in one round
    int fightBarthisRound=0;

    game_framework::CMovingBitmap attack_red;
    Migosp *_enemy;
protected:
    
public:
    Fight()=default;
    ~Fight()=default;

    // the getters
    bool GetEnable();
    bool GetIsAttack();
    std::string GetMinusHP();
    int GetDurationMinusHP();
    int get_current_monster_hp() { return monsterHP; }

    // the setters
    
    // REQUIRED
    // put OnMove, set if the image will be revealed
    void set_fight_enable(bool enable);

    // reset all these to its default state so that when a new round it could start like a new turn
    void ResetDurationMinusHP();
    void ResetMinusHP();
    void ResetIsAttack();
    void ResetIsMiss();

    
    // REQUIRED
    // load and set img for init
    void load_img();
    void set_monster(Migosp *enemy);
    
    // REQUIRED
    // put OnShow, can modify enable to control if img will reveal or not
    void show_fight_img();
    
    // REQUIRED
    // depending on the position, return the value of how much will HP be subtracted
    void attack();

    // to get what damage the enemy will receive
    int Minus(double range);

    // no matter press the enter key or not, we need to detect if it is miss condition
    // so it will be executed in two different places
    void DetectMissCondition();
    
    // to let attack bar gradually moving
    void MovingBar();

    // depending on key in, decide if the bar will stop
    void ToStop(UINT nChar);

    // in order to do the miss condition
    bool GetIsMiss();

    // to show how much attack enemy received
    void RevealMinusHP();

    // after the enter was pressed, the image then show up
    // so it can't be place with load img together
    void ShowHPBar();

    // to let HP bar gradually moving
    void MovingHPBar();

    // to let HP bar unshow, and let enable to be false
    void UnshowHPBar();

    bool is_hp_zero() { return (monsterHP == 0); }
};
