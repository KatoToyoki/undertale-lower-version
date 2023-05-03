#include "stdafx.h"
#include "greater_dog.h"

#include <set>

GreaterDog::GreaterDog()
{
    is_init = true;
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Greater Dog", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_text = GameText({
		Text (60, "* Spare", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_win_text = GameText({
		Text (60, "* YOU WON!", RGB(255,255,255),500, 465,613),
		Text (60, "* You earned 0 XP and 40 gold.", RGB(255,255,255),500, 465,613)},
		talk_mode);
	_is_mercy = false;
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
	Text text0(60, "* It's the Greater Dog.", RGB(255,255,255),600, 465,613);
	 
	text_vector = {text0};
	GameText act_next_round = GameText(text_vector,talk_mode);
	
	Act act_check = {
        "Check",
		act_next_round,
    };
	Act act_pet = {
        "Pet",
		act_next_round,
    };
	Act act_beckon = {
        "Beckon",
		act_next_round,
	};
	Act act_play = {
        "Play",
		act_next_round,
	};
	Act act_ignore = {
        "Ignore",
		act_next_round,
	};
	vector<Act> act_vecter = {act_check,act_pet,act_beckon,act_play,act_ignore};
	acts = Acts (act_vecter) ;
	
}
void GreaterDog::set_act_init(int current_selection)//monster frame那邊的init有隨機性所以多寫了set去把東西包起來
{
	if(!_act_after_enable)
	{
		set_next_round_text();
		act_times = 0;
		_current_selection = current_selection;
	}
}
void GreaterDog::set_act_updata()
{
	text_vector.clear();
	text_vector.shrink_to_fit();
	if (_current_selection == check_d )
	{
		text = dog_text_content.get_reaction("GreaterDogAct","check");
	}
	if (_current_selection == pet_d)
	{
		if (is_play_afb)
		{
			 switch (pet_times)
			 {
			 case 1:
			 	  text = dog_text_content.get_reaction("GreaterDogAct","play_then_pet");
				  break;
			 case 2 :
			 	  text = dog_text_content.get_reaction("GreaterDogAct","last_pet");
				  break;
			 default:
			 	  text = dog_text_content.get_reaction("GreaterDogAct","after_last_pet");
				  break;
			 }
		}
		else if (!is_play_afb && is_pet_afb)
		{
			 text = dog_text_content.get_reaction("GreaterDogAct","after_first_pet");//
			 pet_times=0;
		}
		else if (is_beckon)
		{
			 text = dog_text_content.get_reaction("GreaterDogAct","pet_first_time");//not run
			 pet_times=0;
		}
		else
		{
			 text = dog_text_content.get_reaction("GreaterDogAct","cant_pet");
			 pet_times=0;
		}
	}
	if (_current_selection == beckon_d)
	{
		switch(beckon_times)
		{
		case 1:
			 text = dog_text_content.get_reaction("GreaterDogAct","first_beckon");
			 break;
		default:
			 text = dog_text_content.get_reaction("GreaterDogAct","after_first_beckon");
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
			 	  text = dog_text_content.get_reaction("GreaterDogAct","play_after_pet");
				  break;
			 default:
			 	  text = dog_text_content.get_reaction("GreaterDogAct","after_first_play");
				  break;
			 }
		}
		else
		{
			 text = dog_text_content.get_reaction("GreaterDogAct","cant_play");
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
			 text = dog_text_content.get_reaction("GreaterDogAct","ignore_4");
			 break;
		case 4:
			 text = dog_text_content.get_reaction("GreaterDogAct","ignore_over_4");
			 break;
		}
	}
	 for(unsigned int j=0;j<text[act_times].size();j++)
	 {
		   text_vector.push_back(TEXXT(text[act_times][j]));
	 }
	act_after = GameText(text_vector,talk_mode);
	cost_round = text.size();
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

MonsterText GreaterDog::get_random_game_text(std::string name)
{
	return MonsterText();
}


void GreaterDog::set_monster_frame()
{
	Text data(33, "Mmm, cha", RGB(0,0,0),30, 1234,333);
	Text data2(33, "cha cha!", RGB(0,0,0),30, 1234,382);
	MonsterText neutral = {
		"neutral",
		pass_talk,
		0,
		GameText ({data,data2},monster_mode),
		1,
		{0,2}
	};
	
	_monster_text_vector = {//這邊跟act selection 跑數量要對
		neutral,
		neutral,
		neutral,
		neutral,
		neutral
	};
}
void GreaterDog::set_next_round_text()
{
	Act* act = acts.get_act_by_index(_current_selection);
	Text text0 = TEXXT ("* It's the Greater Dog.");
	GameText game_text = GameText({text0},talk_mode);
	
	if (hp < 50)
	{
		game_text = GameText ({
			Text (60, "* Greater Dog is panting slowly.", RGB(255,255,255),600, 465,613)
		}, talk_mode);
	}
	else if (is_play_afb)
	{
		switch (pet_times)
		{
		case 0:
			game_text = GameText({
				TEXXT("* Greater Dog wants some TLC."),
			},talk_mode);
			break;
		case 1:
			game_text = GameText({
				TEXXT("* Pet capacity is 40-percent."),			
			},talk_mode);
			break;
		default:
			game_text = GameText({
				TEXXT("* Greater Dog is contented."),						
			},talk_mode);
			break;
		}
	}
	else if (is_pet_afb && pet_times == 0)
	{
		game_text = GameText({
			TEXXT("* Greater Dog is patting the"),
			TEXXT("  ground with its front paws.")
		},talk_mode);
	}
	else if(ignore_times >=3)
	{
		game_text = GameText({
			TEXXT("* Greater Dog is making"),
			TEXXT("  puppy-dog eyes.")
		},talk_mode);
	}
	else if (ignore_times > 0 && ignore_times < 3)
	{
		game_text = GameText ({		
			TEXXT ("* Greater Dog just wants"),
			TEXXT ("  affection."),
		}, talk_mode);
	}
	else if (!is_init)
	{
		Text text1;
		std::vector<Text> text_vector;
		switch (act_times_enter%4)
		{
		case 0:
			text0 = TEXXT("* Greater Dog is watching you");
			text1 = TEXXT("  intently.");			
			text_vector = {text0,text1};
			game_text = GameText (text_vector,talk_mode);
			break;
		case 1:
			text0 = TEXXT ("* Greater Dog is waiting for");
			text1 = TEXXT ("  your command.");
			text_vector = {text0,text1};
			game_text = GameText (text_vector,talk_mode);
			break;
		case 2:
			text0 = TEXXT ("* Greater Dog is seeking");
			text1 = TEXXT ("  affection.");
			text_vector = {text0,text1};
			game_text = GameText (text_vector,talk_mode);			
			break;
		case 3:
			text0 = TEXXT ("* It smells like freshly");
			text1 = TEXXT ("  -squeezed puppy juice.");
			text_vector = {text0,text1};
			game_text = GameText (text_vector,talk_mode);
			break;
		}
	}
	
	act->act_next_round = game_text;
}

int GreaterDog::get_next_round_index()
{
	return 0;
}



