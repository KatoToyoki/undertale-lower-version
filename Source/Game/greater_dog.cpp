#include "stdafx.h"
#include "greater_dog.h"

GreaterDog::GreaterDog()
{
	text_content.load("GreaterDogAct");
    is_init = true;
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
		TEXXT(text_content.get_reaction("GreaterDogAct","win_text")[0][0]),
		TEXXT(text_content.get_reaction("GreaterDogAct","win_text")[0][1])
	},
	talk_mode);
}

void GreaterDog::set_img()
{
	set_hp_img();
	enemy_img.LoadBitmapByString({"resources/dog_0.bmp","resources/dog_1.bmp"},RGB(0,0,255));
	enemy_img.SetTopLeft(746,125);
	enemy_img.SetAnimation(300,false);
	
	enemy_img_init.LoadBitmapByString({"resources/dog_0.bmp","resources/dog_1.bmp"},RGB(0,0,255));
	enemy_img_init.SetTopLeft(746,125);
	enemy_img_init.SetAnimation(300,false);

	enemy_img_damege.LoadBitmapByString({"resources/dog_hit.bmp"},RGB(0,0,0));
	enemy_img_damege.SetTopLeft(746,125);

	enemy_barrage.LoadBitmapByString({
 "resources/dog_barage_0.bmp",
 "resources/dog_barage_1.bmp",
 "resources/dog_barage_2.bmp",
	},RGB(0,0,0));
	
	enemy_barrage.SetTopLeft(933,799);
	enemy_barrage.SetAnimation(250,false);
	
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

void GreaterDog::set_barrage()
{
  barrage = Barrage(4,white);
  barrage.loda_CMoving_Bitmap(enemy_barrage);
}

void GreaterDog::set_acts()
{
	Act act_check = {
        "Check",
    };
	Act act_pet = {
        "Pet",
    };
	Act act_beckon = {
        "Beckon",
	};
	Act act_play = {
        "Play",
	};
	Act act_ignore = {
        "Ignore",
	};
	vector<Act> act_vecter = {act_check,act_pet,act_beckon,act_play,act_ignore};
	acts = Acts (act_vecter) ;
}

void GreaterDog::set_act_updata()
{
	set_next_round_text();
	act_text_vector.clear();
	act_text_vector.shrink_to_fit();
	if (_current_selection == check_d )
	{
		act_text = text_content.get_reaction("GreaterDogAct","check");
	}
	if (_current_selection == pet_d)
	{
		if (is_play_afb)
		{
			 switch (pet_times)
			 {
			 case 1:
			 	  act_text = text_content.get_reaction("GreaterDogAct","play_then_pet");
				  break;
			 case 2 :
			 	  act_text = text_content.get_reaction("GreaterDogAct","last_pet");
				  break;
			 default:
			 	  act_text = text_content.get_reaction("GreaterDogAct","after_last_pet");
				  break;
			 }
		}
		else if (!is_play_afb && is_pet_afb)
		{
			 act_text = text_content.get_reaction("GreaterDogAct","after_first_pet");//
			 pet_times=0;
		}
		else if (is_beckon)
		{
			 act_text = text_content.get_reaction("GreaterDogAct","pet_first_time");//not run
			 pet_times=0;
		}
		else
		{
			 act_text = text_content.get_reaction("GreaterDogAct","cant_pet");
			 pet_times=0;
		}
	}
	if (_current_selection == beckon_d)
	{
		switch(beckon_times)
		{
		case 1:
			 act_text = text_content.get_reaction("GreaterDogAct","first_beckon");
			 break;
		default:
			 act_text = text_content.get_reaction("GreaterDogAct","after_first_beckon");
			 break;
		}
	}
	if (_current_selection == play_d)
	{
		if (is_pet_afb)
		{
			 switch (play_times)
			 {
			 case 1:
			 	  act_text = text_content.get_reaction("GreaterDogAct","play_after_pet");
				  break;
			 default:
			 	  act_text = text_content.get_reaction("GreaterDogAct","after_first_play");
				  break;
			 }
		}
		else
		{
			 act_text = text_content.get_reaction("GreaterDogAct","cant_play");
			 play_times=0;
		}
	}
	if (_current_selection == ignore_d)
	{
		switch (ignore_times)
		{
		case 1:
		case 2:
		case 3:
			 act_text = text_content.get_reaction("GreaterDogAct","ignore_4");
			 break;
		case 4:
			 act_text = text_content.get_reaction("GreaterDogAct","ignore_over_4");
			 break;
		}
	}
	 for(unsigned int j=0;j<act_text[act_times].size();j++)
	 {
		   act_text_vector.push_back(TEXXT(act_text[act_times][j]));
	 }
	act_after = GameText(act_text_vector,talk_mode);
	cost_round = act_text.size();
}

void GreaterDog::act_choose_count(UINT nChar)
{
	if ((nChar == VK_RETURN || nChar == 0x5A) && !_act_after_enable)
	{
		is_init = false;
		act_times_enter+=1;
		if (_current_selection == pet_d)
		{
			pet_times+=1;
			if(is_beckon)
			{
				is_pet_afb = true;
			}
		}
		if (_current_selection == beckon_d)
		{
			beckon_times+=1;
			is_beckon = true;
		}
		if (_current_selection == play_d)
		{
			play_times+=1;
			if (is_pet_afb)
			{
				is_play_afb = true;
			}
		}
		if (_current_selection == ignore_d)
		{
			ignore_times+=1;
			if (ignore_times == 4)
			{
				_is_gameover = true;
			}
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

std::vector<std::vector<std::string>> GreaterDog::get_random_text(std::string name)
{
	return {{}};
}

void GreaterDog::set_monster_frame()
{
	monster_frame_mode = pass_talk;
}
void GreaterDog::set_next_round_text()
{
	next_text_vector.clear();
	next_text_vector.shrink_to_fit();
	next_round_text = text_content.get_reaction("GreaterDogAct","new_round_begin");
	
	if (hp < 50)
	{
		next_round_text = text_content.get_reaction("GreaterDogAct","hp_low");
	}
	else if (is_play_afb)
	{
		switch (pet_times)
		{
		case 0:
			next_round_text = text_content.get_reaction("GreaterDogAct","last_pet_count_0");
			break;
		case 1:
			next_round_text = text_content.get_reaction("GreaterDogAct","last_pet_count_1");
			break;
		default:
			next_round_text = text_content.get_reaction("GreaterDogAct","last_pet_count_plus");
			break;
		}
	}
	else if (is_pet_afb && pet_times == 0)
	{
		next_round_text = text_content.get_reaction("GreaterDogAct","afb_play_wait_pet");
	}
	else if(ignore_times >=3)
	{
		next_round_text = text_content.get_reaction("GreaterDogAct","ignore_4_next_round");
	}
	else if (ignore_times > 0 && ignore_times < 3)
	{
		next_round_text = text_content.get_reaction("GreaterDogAct","ignore_over_4_next_round");
	}
	else if (!is_init)
	{
		switch (act_times_enter%4)
		{
		case 0:
			next_round_text = text_content.get_reaction("GreaterDogAct","after_init_1");
			break;
		case 1:
			next_round_text = text_content.get_reaction("GreaterDogAct","after_init_2");
			break;
		case 2:
			next_round_text = text_content.get_reaction("GreaterDogAct","after_init_3");
			break;
		case 3:
			next_round_text = text_content.get_reaction("GreaterDogAct","after_init_4");
			break;
		}
	}
	 for(unsigned int j=0;j<next_round_text[0].size();j++)
	 {
		   next_text_vector.push_back(TEXXT(next_round_text[0][j]));
	 }
	act_next_round = GameText (next_text_vector,talk_mode);
}
