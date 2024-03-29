#include "stdafx.h"
#include "greater_dog.h"

#include "mygame.h"

GreaterDog::GreaterDog()
{
	text_content.load("GreaterDogAct");
	_is_mercy = false;
    _is_init = true;
	monster_exp = 50;
	monster_font = "Determination Mono Web";
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Greater Dog", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_text = GameText({
		Text (60, "* Spare", RGB(255,255,255),500, 465,613)},
		target_mode);
	_is_mercy = false;
	mercy_win_text = GameText({
		TEXXT(text_content.get_reaction("win_text")[0][0]),
		TEXXT(text_content.get_reaction("win_text")[0][1])
	},
	talk_mode);
}

void GreaterDog::init_sub()
{
    ignore_times = 0;
    beckon_times = 0;
    pet_times = 0;
	play_times = 0;
	act_times_enter = 0;
	is_beckon = false;
    is_play_afb = false;
	is_pet_afb = false;
}

void GreaterDog::set_img()
{
	set_hp_img();
    enemy_x = 584;
    enemy_y = 115;
	
	monster_frame_img.LoadBitmapByString({"resources/monster_frame.bmp"},RGB(0,0,0));
	monster_frame_img.SetTopLeft(1129,207);
	
	enemy_img_end_effc.LoadBitmapByString({"resources/enemy_end_effc.bmp"},RGB(0,0,0));
	enemy_img_end_effc.SetTopLeft(enemy_x+250,enemy_y);
	
	enemy_img_init.LoadBitmapByString({"resources/dog_0.bmp","resources/dog_1.bmp"},RGB(0,0,255));
	enemy_img_init.SetTopLeft(enemy_x,enemy_y);
	enemy_img_init.SetAnimation(300,false);

	enemy_img_damege.LoadBitmapByString({"resources/dog_hit.bmp"},RGB(0,0,255));
	enemy_img_damege.SetTopLeft(enemy_x,enemy_y);

	enemy_img_close.LoadBitmapA({"resources/dog_close_0.bmp","resources/dog_close_1.bmp","resources/dog_close_2.bmp","resources/dog_close_2.bmp"},RGB(0,0,255));
	enemy_img_close.SetTopLeft(enemy_x,enemy_y);
	
	enemy_img_end.LoadBitmapByString({"resources/dog_end.bmp"},RGB(0,0,255));
	enemy_img_end.SetTopLeft(enemy_x,enemy_y);

	enemy_img  =enemy_img_init;
	enemy_last  =enemy_img_init;

	red_attck_positon = {960,150};
	fight_bar_positon = {0,374};
}

void GreaterDog::set_hp_img()
{
	enemy_targe_choose_hp.LoadBitmapByString({"resources/enemy_target_mode_hp.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_red.LoadBitmapByString({"resources/enemy_target_mode_hp_red.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_black.LoadBitmapByString({"resources/enemy_target_mode_hp_black.bmp"},RGB(255,255,255));

	hp_bar_x = 1034;
	enemy_targe_choose_hp.SetTopLeft(hp_bar_x,hp_bar_y);
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
	enemy_targe_choose_hp_black.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
}


void GreaterDog::set_acts()
{
	vector<string> act_name_vector = {"Check","Pet","Beckon","Play","Ignore"};
	vector<string> act_vecter = act_name_vector;
	acts = Acts (act_vecter) ;
}

void GreaterDog::set_act_text_updata()
{
	if (ignore_times>0 && ignore_times<4 && !end_fight)
	{
		enemy_img_close.SetFrameIndexOfBitmap(ignore_times-1);
		enemy_img = enemy_img_close;
		enemy_last = enemy_img_close;
	}
	
	std::vector<std::vector<std::string>> act_text = {{}};
	
	if (_current_selection == CHECK_D )
	{
		act_text = text_content.get_reaction("check");
	}
	if (_current_selection == PET_D)
	{
		if (is_play_afb)
		{
			 switch (pet_times)
			 {
			 case 0:
			 	  act_text = text_content.get_reaction("play_then_pet");
				  break;
			 case 1 :
			 	  act_text = text_content.get_reaction("last_pet");
				  break;
			 default:
			 	  act_text = text_content.get_reaction("after_last_pet");
				  break;
			 }
		}
		else if (!is_play_afb && is_pet_afb )
		{
			 act_text = text_content.get_reaction("after_first_pet");//
			 pet_times=0;
		}
		else if (is_beckon)
		{
			 act_text = text_content.get_reaction("pet_first_time");//not run
			 pet_times=0;
		}
		else
		{
			 act_text = text_content.get_reaction("cant_pet");
			 pet_times=0;
		}
	}
	if (_current_selection == BECKON_D)
	{
		switch(beckon_times)
		{
		case 0:
			 act_text = text_content.get_reaction("first_beckon");
			 break;
		default:
			 act_text = text_content.get_reaction("after_first_beckon");
			 break;
		}
	}
	if (_current_selection == PLAY_D)
	{
		if (is_pet_afb)
		{
			 switch (play_times)
			 {
			 case 0:
			 	  act_text = text_content.get_reaction("play_after_pet");
				  break;
			 default:
			 	  act_text = text_content.get_reaction("after_first_play");
				  break;
			 }
		}
		else
		{
			 act_text = text_content.get_reaction("cant_play");
			 play_times=0;
		}
	}
	if (_current_selection == IGNORE_D)
	{
		switch (ignore_times)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			 act_text = text_content.get_reaction("ignore_4");
			 break;
		case 4:
			 act_text = text_content.get_reaction("ignore_over_4");
			 break;
		}
	}

	if (_print_index_act_after)
	{
		act_after = set_vector_vector_to_game_text(act_text,act_times);
		cost_round = act_text.size();
		_print_index_act_after = false;
	}
}

void GreaterDog::act_choose_count(int button_current)
{
	_is_init = false;
	if ( button_current ==1)
	{
		act_times_enter+=1;
		if (_current_selection == PET_D)
		{
			pet_times+=1;
			if(is_beckon)
				is_pet_afb = true;
		}
		if (_current_selection == BECKON_D)
		{
			beckon_times+=1;
			is_beckon = true;
		}
		if (_current_selection == PLAY_D)
		{
			play_times+=1;
			if (is_pet_afb)
				is_play_afb = true;
		}
	}
}

void GreaterDog::check_mercy()
{
	if (is_play_afb && pet_times>1)
	{
		_is_mercy = true;
	}
}

void GreaterDog::set_next_round_text_updata()
{
    std::vector<std::vector<std::string>> next_round_text = {{}};
	next_round_text = text_content.get_reaction("new_round_begin");
	
	if (hp < 50)
	{
		next_round_text = text_content.get_reaction("hp_low");
	}
	else if (is_play_afb)
	{
		switch (pet_times)
		{
		case 0:
			next_round_text = text_content.get_reaction("last_pet_count_0");
			break;
		case 1:
			next_round_text = text_content.get_reaction("last_pet_count_1");
			break;
		default:
			next_round_text = text_content.get_reaction("last_pet_count_plus");
			break;
		}
	}
	else if (is_pet_afb && pet_times == 0)
	{
		next_round_text = text_content.get_reaction("afb_play_wait_pet");
	}
	else if(ignore_times >=4)
	{
		next_round_text = text_content.get_reaction("ignore_4_next_round");
	}
	else if (ignore_times > 0 && ignore_times < 4)
	{
		next_round_text = text_content.get_reaction("ignore_over_4_next_round");
	}
	else if (!_is_init)
	{
		switch (act_times_enter%4)
		{
		case 0:
			next_round_text = text_content.get_reaction("after_init_1");
			break;
		case 1:
			next_round_text = text_content.get_reaction("after_init_2");
			break;
		case 2:
			next_round_text = text_content.get_reaction("after_init_3");
			break;
		case 3:
			next_round_text = text_content.get_reaction("after_init_4");
			break;
		}
	}
	if (_print_index_next_round)
	{
		act_next_round = set_vector_vector_to_game_text(next_round_text,0);
		_print_index_next_round = false;
	}
}

void GreaterDog::set_fight()
{
	ignore_times = 0;
	enemy_last = enemy_img_init;
}

frame_command_c GreaterDog::get_monster_battle_mode()
{
	frame_command_c frame_mode;
	if (greater_dog_round.GetCurrentRound() == 0)
	{
		frame_mode = talk_to_normal_battle;
	}
	else
	{
		frame_mode = talk_to_long_battle;
	}

	return frame_mode;
}

void GreaterDog::fight_open(Move* heart, Character* charactor)
{
	greater_dog_round.SelectRound(heart,charactor);
	greater_dog_round.HPcondition(heart,charactor);
}

bool GreaterDog::get_fight_end()
{
	return greater_dog_round.GetIsAttackEnd();
}

void GreaterDog::init_barrage_data()
{
	if(!greater_dog_round.GetIsSet())
	{
		greater_dog_round.SetAllData();
	}
}

void GreaterDog::show_barrage(Move* heart, Character* charactor,int stege)
{
	if ( stege == game_framework::BATTLE)
	{
		greater_dog_round.SetIsRightTime(true);
		greater_dog_round.RevealBarrage();
		greater_dog_round.DogAnimation(heart,charactor);
	}
}
    
void GreaterDog::to_get_enter_count(UINT nChar, int stage)
{
	if (_current_selection == IGNORE_D && stage == game_framework::CHOOSE_ACT_ITEM &&
		(nChar == VK_RETURN || nChar == 0x5A))
	{
		ignore_times+=1;
		if (ignore_times == 4)
			 _is_gameover = true;
	}
}
