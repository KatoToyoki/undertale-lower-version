#include "stdafx.h"
#include "migosp.h"

Migosp::Migosp()
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
	std::vector<Text> text_vector_pet = {text0,text1,text2,text2,text2,text2,text2};
	act_after = GameText(text_vector,talk_mode);
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

void Migosp::set_act_init(int current_selection)
{
	times = 0;
	_current_selection = current_selection;
	Act* act = acts.get_act_by_index(current_selection);
	if (current_selection == check )
	{
		act->index = 0;
		act->act_after_len_list={0,3};
		act->cost_round = 1;
	}
	if (current_selection == talk)
	{
		act->index = 0;
		act->act_after_len_list={0,0};
		act->cost_round = 0;
	}
	if (current_selection == pet)
	{
		act->index = 0;
		act->act_after_len_list={0,3,1,2};
		act->cost_round = 1;
	}
}

void Migosp::set_game_text_enable(bool enable)
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
		if (times > act->cost_round)
		{
			times+=1;
			*stage-=1;
		}
	}
}

int Migosp::get_now_act_after_index()
{
	Act* act = acts.get_act_by_index(_current_selection);
	act->index+=act->act_after_len_list[times];
	return act->index;
}

int Migosp::get_now_act_after_text_len()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_after_len_list[times+1];
}

GameText Migosp::get_act_after_game_text()
{
	Act* act = acts.get_act_by_index(_current_selection);
	return act->act_after;
}
