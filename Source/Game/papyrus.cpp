#include "stdafx.h"
#include "papyrus.h"

#include "mygame.h"

Papyrus::Papyrus()
{
    text_content.load("PapyrusAct");
    _is_init = true;
	_is_mercy = false;
	round_count = 0;
	monster_exp = 100;
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Papyrus", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_text = GameText({
		Text (60, "* Spare", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_win_text = GameText({
		TEXXT(text_content.get_reaction("win_text")[0][0]),
		TEXXT(text_content.get_reaction("win_text")[0][1])
	},
	talk_mode);
	next_round_text = text_content.get_reaction("init");
}
void Papyrus::init_sub()
{
	_is_first_mercy_or_attck = false;
	_is_flirt = false;
	round_count = 0;
	flirt_count = 0;
	flirt_after_count = 0;
	insult_count = 0;
}

void Papyrus::set_img()
{
	set_hp_img();
    enemy_x = 800;
    enemy_y = 75;
	
	monster_frame_img.LoadBitmapByString({"resources/monster_frame_p.bmp"},RGB(0,0,0));
	monster_frame_img.SetTopLeft(1129,207);
	
	enemy_img_end_effc.LoadBitmapByString({"resources/enemy_end_effc.bmp"},RGB(0,0,0));
	enemy_img_end_effc.SetTopLeft(enemy_x,enemy_y);
	
	enemy_img_init.LoadBitmapByString({"resources/papyrus.bmp"},RGB(0,0,0));
	enemy_img_init.SetTopLeft(enemy_x,enemy_y);

	enemy_img_damege.LoadBitmapByString({"resources/papyrus_hit.bmp"},RGB(0,0,0));
	enemy_img_damege.SetTopLeft(enemy_x,enemy_y);

	enemy_img_end.LoadBitmapByString({"resources/papyrus_end.bmp"},RGB(0,0,0));
	enemy_img_end.SetTopLeft(enemy_x,enemy_y);

	enemy_img  =enemy_img_init;
	enemy_last  =enemy_img_init;

	red_attck_positon = {865,192};
	fight_bar_positon = {0,374};
}
	
void Papyrus::set_hp_img()
{
	enemy_targe_choose_hp.LoadBitmapByString({"resources/enemy_target_mode_hp.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_red.LoadBitmapByString({"resources/enemy_target_mode_hp_red.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_black.LoadBitmapByString({"resources/enemy_target_mode_hp_black.bmp"},RGB(255,255,255));

	hp_bar_x = 900;
	enemy_targe_choose_hp.SetTopLeft(hp_bar_x,hp_bar_y);
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
	enemy_targe_choose_hp_black.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
}
void Papyrus::set_acts()
{
	vector<string> act_name_vector = {"Check","flirt","insult"};
	vector<string> act_vecter = act_name_vector;
	acts = Acts (act_vecter);
}

void Papyrus::set_act_text_updata()
{
	std::vector<std::vector<std::string>> act_text = {{}};

	switch (_current_selection)
	{
	case CHECK_P:
		act_text = text_content.get_reaction("check");
		break;
	case FLIRT_P:
		if (_is_first_mercy_or_attck)
			act_text = text_content.get_reaction("after_fight_flirt");
		else if (flirt_count >=3)
			act_text = text_content.get_reaction("flirt_three_times");
		break;
	case INSULT_P:
		if (_is_first_mercy_or_attck)
			act_text = text_content.get_reaction("after_fight_insult");
		else if (insult_count >=2)
			act_text = text_content.get_reaction("insult_three_times");
		break;
	}
	
	act_after = set_vector_vector_to_game_text(act_text,act_times);
	cost_round = act_text.size();

	if ((_current_selection == FLIRT_P && flirt_count < 3) ||
		(_current_selection == INSULT_P && insult_count < 2))
	{
		std::vector<std::vector<std::string>> vector = {{}};
		act_text = vector;
		cost_round = 0;
	}
}

void Papyrus::set_next_round_text_updata()
{
	if (_is_init)
		next_round_text = text_content.get_reaction("init");
	else if (hp < 50)
		next_round_text = text_content.get_reaction("hp_low");
	else if (_is_first_mercy_or_attck && round_count == 1)
		next_round_text = text_content.get_reaction("first_fight_mercy_next_round");
	else if (_is_first_mercy_or_attck && round_count == 18)//maybe see
		next_round_text = text_content.get_reaction("round18_next_round");
	else if (_is_first_mercy_or_attck && round_count >= 19)//maybe see
		next_round_text = text_content.get_reaction("end_next_round");
	else if (flirt_after_count > 0 && flirt_after_count < 10)
		next_round_text = text_content.get_reaction("flirt_next_round_"+std::to_string(flirt_after_count-1));
	
	act_next_round = set_vector_vector_to_game_text(next_round_text,0);
}

void Papyrus::act_choose_count(int button_current)
{
	_is_init = false;
	//next_round random
	next_round_text = text_content.get_reaction("after_init_next_round");
	if (button_current == 1)
	{
		if (_current_selection == FLIRT_P && flirt_count < 3)
		{
			_is_flirt = true;
			flirt_count+=1;
		}
		if (_current_selection == INSULT_P && insult_count < 2)
		{
			insult_count+=1;
		}
	}
	if (_is_flirt && flirt_after_count < 10)
	{
		flirt_after_count+=1;
	}
	
	if (_is_first_mercy_or_attck)
	{
		round_count+=1;
		flirt_count = 3;
		insult_count = 2;
	}
}

void Papyrus::set_monster_frame_before()
{
	monster_frame_mode_before_battle = enter_talk;
	monster_text = text_content.get_reaction("flirt_monster_talk_0");
	//no first mercy or fight
	if (_is_first_mercy_or_attck && round_count <20)
		monster_text = text_content.get_reaction("round"+to_string(round_count)+"_monster_talk");
	else if (_current_selection == CHECK_P)
		monster_text = text_content.get_reaction("init_check_monster_talk");
	else if (_current_selection == FLIRT_P)
		monster_text = text_content.get_reaction("flirt_monster_talk_"+to_string(flirt_count));
	else if (_current_selection == INSULT_P)
		monster_text = text_content.get_reaction("insult_monster_talk_"+to_string(insult_count));

	
	monster_frame_game_text_before_battle = set_vector_vector_to_game_text(monster_text,monster_times_before,monster_mode_2);
	monster_cost_round_before = monster_text.size();
}

void Papyrus::set_monster_frame_after()
{
	monster_frame_mode_after_battle = pass_talk;
	monster_text = text_content.get_reaction("round19_after_battle");
	
	if (_is_first_mercy_or_attck && round_count == 0)
	{
		monster_text = text_content.get_reaction("after_fight_mercy_after_battle");
		monster_frame_mode_after_battle = enter_talk;
	}
	else if (round_count == 18 || round_count == 19)
	{
		monster_text = text_content.get_reaction("round"+ to_string(round_count)+"_after_battle");
		monster_frame_mode_after_battle = enter_talk;
	}
	
	monster_frame_game_text_after_battle = set_vector_vector_to_game_text(monster_text,monster_times_after,monster_mode_2);
	monster_cost_round_after = monster_text.size();
}

void Papyrus::check_mercy()
{
	if (round_count >= 20)
	{
		_is_mercy = true;
	}
}

frame_command_c Papyrus::get_monster_battle_mode()
{
	return talk_to_papyrus_normal_battle;
}

void Papyrus::fight_open(Move* heart, Character* charactor)
{
	papyrus_round.SelectRound(heart,charactor);
	papyrus_round.HPcondition(heart,charactor);
}

bool Papyrus::get_fight_end()
{
	return papyrus_round.GetIsAttackEnd();
}

void Papyrus::init_barrage_data()
{
	if(!papyrus_round.GetIsSet())
	{
		if (!_is_first_mercy_or_attck)
			papyrus_round.SetAllData(-1);
		else
			papyrus_round.SetAllData(round_count);
	}
}

void Papyrus::show_barrage(Move* heart, Character* charactor,int stege)
{
	if ( stege == game_framework::BATTLE)
	{
		papyrus_round.SetIsRightTime(true);
		papyrus_round.RevealBarrage();
		papyrus_round.DogAnimation(heart,charactor);
	}
	//笨狗特判 改round_count 偵測笨狗回合
	if ( (stege == game_framework::BATTLE ||
		 stege == game_framework::BATTLE_AFTER_MONSTER_FRAME) && round_count == 18
		 )
	{
		papyrus_round.SetIsRightTime(true);
		papyrus_round.RevealBarrage();
		papyrus_round.DogAnimation(heart,charactor);
	}
	
}

void Papyrus::set_fight()
{
	_is_first_mercy_or_attck = true;
}

void Papyrus::set_mercy()
{
	_is_first_mercy_or_attck = true;
	papyrus_round.set_is_set(false);
	init_barrage_data();
}

void Papyrus::to_get_enter_count(UINT nChar, int stage)
{
    papyrus_round.ToGetEnterCount(nChar);
}

bool Papyrus::GetIsBlue()
{
	return papyrus_round.GetIsBlue();
}