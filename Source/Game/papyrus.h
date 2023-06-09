#pragma once
#include "enemy.h"
#include "PapyrusRound.h"

enum papyrus_act_selection
{
    CHECK_P,
    FLIRT_P,
    INSULT_P
};

class Papyrus : public Enemy
{
public:
    Papyrus();
    void init_sub() override;
    void set_img() override;
    void set_hp_img() override;
    void set_acts() override;
    void set_act_text_updata() override;
    void act_choose_count(int button_current) override;
    void set_monster_frame_before() override;
    void set_monster_frame_after() override;
    void set_next_round_text_updata() override;

    frame_command_c get_monster_battle_mode() override ;
    
    void set_fight() override;//這個會在fight裡面被呼叫 功用是如果怪物被打了會做什麼變化之類的
    void set_mercy() override;//game_manager choose_mercy_after call  功用是如果怪物被mercy會做什麼變化之類的
    void fight_open(Move* heart, Character* charactor) override;
    bool get_fight_end() override;
    void show_barrage(Move* heart, Character* charactor,int stage) override;
    void init_barrage_data() override;//用來init彈幕資料
    void to_get_enter_count(UINT nChar, int stage) override;

    void check_mercy() override;

    bool GetIsBlue();

    void Test2()
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 250, "round "+to_string(papyrus_round.GetCurrentRound()));
        game_framework::CDDraw::ReleaseBackCDC();
    }
    
private:
    bool _is_first_mercy_or_attck = false;
    bool _is_first_mercy = false;
    bool _is_first_attck = false;
    bool _is_flirt = false;
    int round_count = 0;
    int flirt_count = 0;
    int flirt_after_count = 0;
    int insult_count = 0;
    int max_round = 21;
    
    PapyrusRound papyrus_round;
};
