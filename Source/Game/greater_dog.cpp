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

	enemy_targe_choose_hp.SetTopLeft(hp_bar_x+150,hp_bar_y);
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth()+150,hp_bar_y);
	enemy_targe_choose_hp_black.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth()+150,hp_bar_y);
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

	text0 = Text (60, "* Greater Dog curls up", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  in your lab", RGB(255,255,255),600, 465,613);
	text2 = Text (60, "  as it is pet by you.", RGB(255,255,255),600, 465,613);
	Text text3(60, "* It gets so comfortable", RGB(255,255,255),600, 465,613);
	Text text4(60, "  it falls asleep...", RGB(255,255,255),600, 465,613);
	Text text5(60, "* Zzzzz...", RGB(255,255,255),600, 465,613);
	Text text6(60, "* ...", RGB(255,255,255),600, 465,613);
	Text text7(60, "* Then it wakes up!", RGB(255,255,255),600, 465,613);
	Text text8(60, "* It's so excited!", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1,text2,text3,text4,text5,text6,text7,text8};
	GameText act_after_pet = GameText(text_vector,talk_mode);

	text0 = Text (60, "* The Greater Dog's ears", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  perk up.", RGB(255,255,255),600, 465,613);
	text2 = Text (60, "* Nothing eles happens.", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1,text2};
	GameText act_after_beckon = GameText(text_vector,talk_mode);

	text0 = Text (60, "* Greater Dog is not excited", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  enough to play with.", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1};
	GameText act_after_play = GameText(text_vector,talk_mode);
	
	text0 = Text (60, "* Greater Dog inches closer.", RGB(255,255,255),600, 465,613);
	text_vector = {text0};
	GameText act_after_ignore = GameText(text_vector,talk_mode);
	
	text0 = Text (60, "* Greater Dog is waiting for", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  your command.", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1};
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
		5,
		{0,3,2,1,1,2}
    };
	Act act_beckon = {
        "Beckon",
        act_after_beckon,
		act_next_round,
		0,
		1,
		{0,3}
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
			act->index = 0;
			act->act_after_len_list={0,3};
			act->cost_round = 1;
		}
		if (_current_selection == pet_d)
		{
			act->index = 0;
			act->act_after_len_list={0,3,2,1,1,2};
			act->cost_round = 5;
		}
		if (_current_selection == beckon_d)
		{
			act->index = 0;
			act->act_after_len_list={0,3};
			act->cost_round = 1;
		}
		if (_current_selection == play_d)
		{
			act->index = 0;
			act->act_after_len_list={0,2};
			act->cost_round = 1;
		}
		if (_current_selection == ignore_d)
		{
			act->index = 0;
			act->act_after_len_list={0,1};
			act->cost_round = 1;
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
			Text (60, "* Migosp refuses to give up.", RGB(255,255,255),600, 465,613)
		}, talk_mode);
		
		act->act_next_round = game_text;
	}
}

int GreaterDog::get_next_round_index()
{
	return 0;
}



