#include "stdafx.h"
#include "migosp.h"

Migosp::Migosp()
{
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Migosp", RGB(255,255,255),500, 465,613)},
		target_mode);
}
void Migosp::set_img()
{
	enemy_img.LoadBitmapByString({"resources/migosp_0.bmp","resources/migosp_1.bmp"},RGB(255,255,255));
	enemy_img.SetTopLeft(993,316);
	enemy_img.SetAnimation(300,false);

	enemy_targe_choose_hp.LoadBitmapByString({"resources/enemy_target_mode_hp.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_red.LoadBitmapByString({"resources/enemy_target_mode_hp_red.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_black.LoadBitmapByString({"resources/enemy_target_mode_hp_black.bmp"},RGB(255,255,255));

	enemy_targe_choose_hp.SetTopLeft(hp_bar_x,hp_bar_y);
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
	enemy_targe_choose_hp_black.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
}

void Migosp::show_img()
{
	enemy_img.ShowBitmap();
}

void Migosp::set_enemy_targe_choose_hp_bar(bool enable)
{
	_choose_targe_hp_bar_enable = enable;
}

void Migosp::show_enemy_targe_choose_hp_bar()
{
	if (_choose_targe_hp_bar_enable)
	{
		enemy_targe_choose_hp.ShowBitmap();
		enemy_targe_choose_hp_red.ShowBitmap();
		enemy_targe_choose_hp_black.ShowBitmap();
	}
}

void Migosp::updata_hp_bar_by_hp()
{
	const float hp_percent = static_cast<float>(hp) / static_cast<float>(hp_max);
	const int hp_bar_percent_width = static_cast<int>(hp_percent * enemy_targe_choose_hp.GetWidth());
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x + hp_bar_percent_width,hp_bar_y);
}

void Migosp::set_acts()
{
	Text text0(60, "* Migosp - AT 7 DF 5", RGB(255,255,255),600, 465,613);
	Text text1(60, "* It seems evil,but it's just ", RGB(255,255,255),600, 465,613);
	Text text2(60, "  with the wrong crowd...", RGB(255,255,255),600, 465,613);
	std::vector<Text> text_vector = {text0,text1,text2};
	GameText act_after = GameText(text_vector,talk_mode);

	text0 = Text (60, "* Migosp doesn't have a care", RGB(255,255,255),600, 465,613);
	text1 = Text (60, "  in the world.", RGB(255,255,255),600, 465,613);
	text_vector = {text0,text1};
	GameText act_next_round = GameText(text_vector,talk_mode);

	Act act_check = {
        "check",
        act_after,
		act_next_round,
		1,
		1,
		{0,3}
    };
	Act act_talk = {
        "talk",
        act_after,
		act_next_round,
		0,
		0,
		{0,3}
    };
	Act act_pet = {
        "pet",
        act_after,
		act_next_round,
		0,
		2,
		{0,2,3}
    };
	vector<Act> act_vecter = {act_check,act_talk,act_pet};
	acts = Acts (act_vecter) ;
	
}


void Migosp::set_act_init(int current_selection)//monster frame那邊的init有隨機性所以多寫了set去把東西包起來
{
	set_next_round_text();
	
	act_times = 0;
	_current_selection = current_selection;
	Act* act = acts.get_act_by_index(_current_selection);
	if (_current_selection == check )
	{
		act->index = 0;
		act->act_after_len_list={0,3};
		act->cost_round = 1;
	}
	if (_current_selection == talk)
	{
		act->index = 0;
		act->act_after_len_list={0,0};
		act->cost_round = 0;
	}
	if (_current_selection == pet)
	{
		act->index = 0;
		act->act_after_len_list={0,1,1,1};
		act->cost_round = 3;
	}
}

void Migosp::set_act_game_text_enable(bool enable)
{
	_act_after_enable = enable;
	if (_act_after_enable )
	{
		Act* act = acts.get_act_by_index(_current_selection);
		if (act->cost_round == 0)
		{
			*_stege+=1;
		}
	}
}

void Migosp::act_after_stage_control_updata(UINT nChar, int* stage)
{
	_stege = stage;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _act_after_enable)
	{
		Act* act = acts.get_act_by_index(_current_selection);
		if (act_times < act->cost_round-1)
		{
			act_times+=1;
			act->index+=act->act_after_len_list[act_times];
			*stage-=1;
		}
	}
}

int Migosp::get_now_act_after_index()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->index;
}

int Migosp::get_now_act_after_text_len()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_after_len_list[act_times+1];
}

GameText Migosp::get_act_after_game_text()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_after;
}

int Migosp::generate_random_num(int min, int max)
{
    return ( rand() % ((max-1) - min + 1) + min );
}

MonsterText Migosp::get_random_game_text(std::string name)
{
	if(name == "neutral")
	{
		Text data(33, "Mmm, cha", RGB(0,0,0),30, 1234,333);
		Text data2(33, "cha cha!", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_1 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2},monster_mode),
			1,
			{0,2}
		};
		data = Text(33, "Mmm, cha", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "cha cha!", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_2 = {
			"neutral",
			enter_talk,
			0,
			GameText ({data2,data},monster_mode),
			2,
			{0,1,1}
		};
		
		
		vector<MonsterText> game_text_vector =  {
			neutral_1,
			neutral_2
		};
		int random_num = generate_random_num(0,game_text_vector.size());
		return game_text_vector[random_num];
	}
	return MonsterText();
}


void Migosp::set_monster_frame()
{
	MonsterText neutral = get_random_game_text("neutral");
	
	Text data(33, "suus", RGB(0,0,0),30, 1234,333);
	Text data2(33, "sus", RGB(0,0,0),30, 1234,382);
	MonsterText sus = {
		"sus",
		no_enter_talk,
		0,
		GameText ({data,data2},monster_mode),
		1,
		{0,2}
	};
	_monster_text_vector = {//這邊跟act selection 跑
		neutral,
		neutral,
		sus
	};
}

void Migosp::set_monster_frame_init(int current_selection)
{
	monster_times = 0;
	set_monster_frame();
}

GameText Migosp::get_monster_frame_game_text()
{
    return _monster_text_vector[_current_selection].game_text;
}

int Migosp::get_now_monster_frame_after_index()
{
    return _monster_text_vector[_current_selection].index;
}

int Migosp::get_now_monster_frame_after_text_len()
{
    return _monster_text_vector[_current_selection].round_len_list[monster_times+1];
}

int Migosp::get_now_monster_frame_mode()
{
    return _monster_text_vector[_current_selection].mode;
}

void Migosp::monster_frame_stage_control_updata(UINT nChar, int* stage,MonsterFrame *monster_frame)
{
	_stege = stage;
	_monster_frame = monster_frame;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _monster_frame_enable)
	{
		MonsterText *monster_text = &_monster_text_vector[_current_selection];
		if (monster_times < monster_text->cost_round-1)
		{
			monster_times+=1;
			monster_text->index+=monster_text->round_len_list[monster_times];
			*stage-=1;
		}
	}
}

void Migosp::set_monster_frame_game_text_enable(bool enable)
{
	_monster_frame_enable = enable;
	if (_monster_frame_enable)
	{
		MonsterText *monster_text = &_monster_text_vector[_current_selection];
		if (monster_text->mode == no_enter_talk )
		{
			*_stege+=1;
		}
	}
}

void Migosp::set_next_round_text()
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

GameText Migosp::get_next_round_game_text()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_next_round;
}

int Migosp::get_next_round_index()
{
	return 0;
}

int Migosp::get_next_round_text_len()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_next_round.get_vector_len();
}


