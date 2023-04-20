#include "stdafx.h"
#include "greater_dog.h"

GreaterDog::GreaterDog()
{
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
	Text text0(60, "* GREATER DOG - AT 15 DF 8", RGB(255,255,255),600, 465,613);
	Text text1(60, "* It's so excited that it", RGB(255,255,255),600, 465,613);
	Text text2(60, "  thinks fighting is just play.", RGB(255,255,255),600, 465,613);
	std::vector<Text> text_vector = {text0,text1,text2};
	GameText act_after = GameText(text_vector,talk_mode);

	text0 = Text (60, "* Greater Dog is too far", RGB(255,255,255),600, 465,613);//init
	text1 = Text (60, "  away to pet.", RGB(255,255,255),600, 465,613);
	text2 = Text (60, "* You just pet the air.", RGB(255,255,255),600, 465,613);
	
	Text text3(60, "* Greater Dog curls up", RGB(255,255,255),600, 465,613);//afb
	Text text4(60, "  in your lab", RGB(255,255,255),600, 465,613);
	Text text5(60, "  as it is pet by you.", RGB(255,255,255),600, 465,613);
	Text text6(60, "* It gets so comfortable", RGB(255,255,255),600, 465,613);
	Text text7(60, "  it falls asleep...", RGB(255,255,255),600, 465,613);
	Text text8(60, "* Zzzzz...", RGB(255,255,255),600, 465,613);
	Text text9(60, "* ...", RGB(255,255,255),600, 465,613);
	Text text10(60, "* Then it wakes up!", RGB(255,255,255),600, 465,613);
	Text text11(60, "* It's so excited!", RGB(255,255,255),600, 465,613);
	
	Text text12 = TEXXT("* Greater Dog's excitement is");
	Text text13 = TEXXT("  creating a power field that");
	Text text14 = TEXXT("  prevents petting.");

	Text text15 = TEXXT("* As you pet the dog,");//1
	Text text16 = TEXXT("  it sinks its entire weight");
	Text text17 = TEXXT("  into you...");
	Text text18 = TEXXT("* You movements slows.");
	Text text19 = TEXXT("* But, you still haven't");
	Text text20 = TEXXT("  pet enough...!");
	
	Text text21 = TEXXT("* You pet decisively.");//2
	Text text22 = TEXXT("* Pet capacity reaches 100");
	Text text23 = TEXXT("  percent.");
	Text text24 = TEXXT("* The dog flops over with");
	Text text25 = TEXXT("  its legs hanging in the air.");
	
	Text text26 = TEXXT("* Tummy rubs are forbidden.");//plus
	text_vector = {text0,text1,text2,text3,text4,text5,text6,text7,text8,text9,text10,text11,
	 text12,text13,text14,text15,text16,text17,text18,text19,text20,text21,text22,text23,text24,text25,text26
	};
	GameText act_after_pet = GameText(text_vector,talk_mode);

	text0 = Text (60, "* You call the Greater Dog.", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "* It bounds towards you,", RGB(255,255,255),600, 465,613);
	text2 = Text (60, "  flecking slobber into your", RGB(255,255,255),600, 465,613);
	text3 = Text (60, "  face.", RGB(255,255,255),600, 465,613);
	text4 = Text (60, "* The Greater Dog's ears", RGB(255,255,255),600, 465,613);
	text5 = Text (60, "  perk up.", RGB(255,255,255),600, 465,613);
	text6 = Text (60, "* Nothing eles happens.", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1,text2,text3,text4,text5,text6};
	GameText act_after_beckon = GameText(text_vector,talk_mode);

	text0 = Text (60, "* Greater Dog is not excited", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  enough to play with.", RGB(255,255,255),600, 465,613);
	text2  = TEXXT("* You make a snowball and");
	text3  = TEXXT("  throw it for the dog");
	text4  = TEXXT("  to fetch.");
	text5  = TEXXT("* It splats on the ground.");
	text6  = TEXXT("* Greater Dog picks up all");
	text7  = TEXXT("  the snow in the area");
	text8  = TEXXT("  and brings it to you.");
	text9 = TEXXT("* Now dog is very tired...");
	text10 = TEXXT("* It rests its head on you...");
	text11 = TEXXT("* Greater Dog is too tired");
	text12 = TEXXT("  to play.");
	text_vector = {text0,text1,text2,text3,text4,text5,text6,text7,text8,text9,text10,text11,text12};
	GameText act_after_play = GameText(text_vector,talk_mode);

	text0 = TEXXT("* Greater Dog inches closer.");
	// text1 = Text (60, "* Greater Dog is making", RGB(255,255,255),600, 465,613);
	// text2 = Text (60, "  puppy-dog eyes.", RGB(255,255,255),600, 465,613);
	text1  = TEXXT("* Greater Dog decides you are");
	text2  = TEXXT("  too boring.");
	text_vector = {text0,text1,text2};
	GameText act_after_ignore = GameText(text_vector,talk_mode);
	
	// text0 = Text (60, "* Greater Dog is waiting for", RGB(255,255,255),600, 465,613);
	// text1 = Text (60, "  your command.", RGB(255,255,255),600, 465,613);
	text0 = Text (60, "* It's the Greater Dog.", RGB(255,255,255),600, 465,613);
	text_vector = {text0};
	GameText act_next_round = GameText(text_vector,talk_mode);
	
	Act act_check = {
        "Check",
        act_after,
		act_next_round,
		0,
		1,
		{0,3}
    };
	Act act_pet = {
        "Pet",
        act_after_pet,
		act_next_round,
		0,
		1,
		{0,3}
    };
	Act act_beckon = {
        "Beckon",
        act_after_beckon,
		act_next_round,
		0,
		2,
		{0,1,3}
	};
	Act act_play = {
        "Play",
        act_after_play,
		act_next_round,
		0,
		1,
		{0,2}
	};
	Act act_ignore = {
        "Ignore",
        act_after_ignore,
		act_next_round,
		0,
		1,
		{0,1}
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
		Act* act = acts.get_act_by_index(_current_selection);
		if (_current_selection == check_d )
		{
			set_act_init(act,0,{0,3},1);
		}
		if (_current_selection == pet_d)
		{
			switch (pet_times)
			{
			case 0:
				set_dog_init_pet(act,before_beckon);
				break;
			case 1:
				set_dog_init_pet(act,after_ignore_or_beckon);
				break;
			case 2:
				set_dog_init_pet(act,before_play_afb);
				break;
			case 3:
				set_dog_init_pet(act,after_play_pet_1_afb);
				break;
			case 4:
				set_dog_init_pet(act,after_play_pet_2_afb);
				break;
			default:
				set_dog_init_pet(act,after_play_pet_plus_afb);
				break;
			}
		}
		if (_current_selection == beckon_d)
		{
			switch(beckon_times)
			{
			case 0:
				set_act_init(act,0,{0,1,3},2);
				break;
			default:
				set_act_init(act,4,{0,3},1);
				break;
			}
		}
		if (_current_selection == play_d)
		{
			switch (play_times)
			{
			case 0:
				set_dog_init_play(act,not_excited);
				break;
			case 1:
				set_dog_init_play(act,excited);
				break;
			default:
				set_dog_init_play(act,after_excited_plus);
				break;
			}
		}
		if (_current_selection == ignore_d)
		{
			switch (ignore_times)
			{
			case 0:
			case 1:
			case 2:
				set_act_init(act,0,{0,1},1);
				break;
			case 3:
				set_act_init(act,1,{0,2},1);
				break;
			}
		}
	}
}

void GreaterDog::set_act_init(Act* act, int index, vector<int> list, int round)
{
	act->index = index;
	act->act_after_len_list = list;
	act->cost_round = round;
}
void GreaterDog::set_dog_init_pet(Act *act,dog_act_pet num)
{
	switch (num)
	{
	case before_beckon:
		set_act_init(act,0,{0,3},1);
		break;
	case after_ignore_or_beckon:
		set_act_init(act,3,{0,3,2,1,1,2},5);
		break;
	case before_play_afb:
		set_act_init(act,12,{0,3},1);
		break;
	case after_play_pet_1_afb:
		set_act_init(act,15,{0,3,1,2},3);
		break;
	case after_play_pet_2_afb:
		set_act_init(act,21,{0,3,2},2);
		break;
	case after_play_pet_plus_afb:
		set_act_init(act,26,{0,1},1);
		break;
	}
}

void GreaterDog::set_dog_init_play(Act *act, dog_act_play num)
{
	switch (num)
	{
	case not_excited:
		set_act_init(act,0,{0,2},1);
		break;
	case excited:
		set_act_init(act,2,{0,3,1,3,2},4);
		break;
	case after_excited_plus:
		set_act_init(act,10,{0,2},1);
		break;
	}
}

void GreaterDog::act_choose_count(UINT nChar)
{
	if ((nChar == VK_RETURN || nChar == 0x5A) && !_act_after_enable)
	{
		if (_current_selection == check_d )
		{
		}
		if (_current_selection == pet_d)
		{
			pet_times+=1;
		}
		if (_current_selection == beckon_d)
		{
			beckon_times+=1;
			is_beckon = true;
		}
		if (_current_selection == play_d)
		{
			play_times+=1;
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
	if (_current_selection == pet_d)
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
	if (hp < 50)
	{
		GameText game_text ({
			Text (60, "* Greater Dog is panting slowly.", RGB(255,255,255),600, 465,613)
		}, talk_mode);
		
		act->act_next_round = game_text;
	}
}

int GreaterDog::get_next_round_index()
{
	return 0;
}



