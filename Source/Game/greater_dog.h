#pragma once
#include "enemy.h"
#include "GreaterDogRound.h"
#include "TextContent.h"

enum dog_act_selection
{
    check_d,
    pet_d,
    beckon_d,
    play_d,
    ignore_d
};

class GreaterDog : public Enemy
{
public:
    GreaterDog();
    //set enemy normal img & damege img & red attcke posion & fight attck bar positon & barrage
    void set_img() override;
    void set_hp_img() override;//set choose fight target need set the hp bar x postion
    void set_barrage() override;//now only migosp barrage dont read json so use this
    void set_acts() override;//set enemy act list
    //設定 判斷什麼條件之中 選擇完act後 在user_frame內 接下來該顯示的字
    void set_act_text_updata() override;//here run by 每偵
    //設定 按下enter後什麼條件會成立 如果要計數該選擇做了幾次也在這裡進行加減
    void act_choose_count(UINT nChar,int button_current) override;
    //同上的set_act_text_updata 只是從在user_frame顯示變成在monster_frame顯示
    void set_monster_frame() override;
    //同上的set_act_text_updata 設定的文字 是下一回合該顯示的字
    void set_next_round_text_updata() override;

    std::vector<std::vector<std::string>> get_random_text(std::string name) override;
    //在game_run的流程會統一call這個function所以如果需要更改戰鬥使用的眶 在這裏面判斷回傳的東西
    frame_command get_monster_battle_mode() override;
    void set_fight() override;//這個會在fight裡面被呼叫 功用是如果怪物被打了會做什麼變化之類的
    void fight_open(Move* heart, Character* charactor) override;// 這裡面會選擇回合跟進行扣寫(大概吧)
    bool get_fight_end() override;//這裡面用來回傳判斷該回合戰鬥結束的條件 結束就true 還沒結束就false
    void init_barrage_data() override;//用來init彈幕資料
    void show_barrage(Move* heart, Character* charactor, int stage) override;//判斷該enemy的彈幕們何時顯示
    
    void check_mercy() override;//mercy條件寫在這裡 條件齊了就改變is_mercy
private:
    int ignore_times = 0;
    int beckon_times = 0;
    int pet_times = 0;
    int play_times = 0;
    int act_times_enter = 0;
    bool is_beckon = false;
    bool is_play_afb = false;//play過在b之後
    bool is_pet_afb = false;//pet過在b之後
    bool is_init = true;

    game_framework::CMovingBitmap enemy_img_close;
    GreaterDogRound greater_dog_round;
};
