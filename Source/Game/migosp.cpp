#include "stdafx.h"
#include "migosp.h"

#include "barrage.h"

Migosp::Migosp()
{
	text_content.load("MigospAct");
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Migosp", RGB(255,255,255),500, 465,613)},
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

void Migosp::set_img()
{
	set_hp_img();
	enemy_img_init.LoadBitmapByString({"resources/migosp_0.bmp","resources/migosp_1.bmp"},RGB(0,0,0));
	enemy_img_init.SetTopLeft(993,316);
	enemy_img_init.SetAnimation(300,false);

	enemy_img_damege.LoadBitmapByString({"resources/migosp_hit.bmp"},RGB(0,0,0));
	enemy_img_damege.SetTopLeft(993,316);

	enemy_img = enemy_img_init;
	enemy_last = enemy_img_init;

	red_attck_positon = {1050,316};
	fight_bar_positon = {0,200};
	
	enemy_barrage.LoadBitmapByString({
 "resources/std_hand_up.bmp",
   "resources/hand_up.bmp","resources/std.bmp",
      "resources/hand_up.bmp","resources/std.bmp",
	"resources/hand_down.bmp","resources/std.bmp",
	"resources/hand_down.bmp","resources/std.bmp",
	"resources/act_0.bmp","resources/act_1.bmp",
	"resources/act_2.bmp","resources/act_3.bmp",
	"resources/act_4.bmp","resources/act_5.bmp",
	"resources/std.bmp"
	},RGB(0,0,0));
	
	enemy_barrage.SetTopLeft(933,799);
	enemy_barrage.SetAnimation(250,false);
}

void Migosp::set_hp_img()
{
	enemy_targe_choose_hp.LoadBitmapByString({"resources/enemy_target_mode_hp.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_red.LoadBitmapByString({"resources/enemy_target_mode_hp_red.bmp"},RGB(255,255,255));
	enemy_targe_choose_hp_black.LoadBitmapByString({"resources/enemy_target_mode_hp_black.bmp"},RGB(255,255,255));

    hp_bar_x = 884;
	enemy_targe_choose_hp.SetTopLeft(hp_bar_x,hp_bar_y);
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
	enemy_targe_choose_hp_black.SetTopLeft(hp_bar_x+enemy_targe_choose_hp.GetWidth(),hp_bar_y);
}

void Migosp::set_barrage()
{
  barrage = Barrage(3,white);
  barrage.loda_CMoving_Bitmap(enemy_barrage);
}

void Migosp::set_acts()
{
	Act act_check = {
        "check",
    };
	Act act_talk = {
        "talk",
    };
	vector<Act> act_vecter = {act_check,act_talk};
	acts = Acts (act_vecter) ;
}
void Migosp::set_act_text_updata()
{
	act_text_vector.clear();
	act_text_vector.shrink_to_fit();
	if (_current_selection == check_m )
	{
		act_text = text_content.get_reaction("check");
	}
	 for(unsigned int j=0;j<act_text[act_times].size();j++)
	 {
	 	act_text_vector.push_back(TEXXT(act_text[act_times][j]));
	 }
	act_after = GameText(act_text_vector,talk_mode);
	cost_round = act_text.size();
	
	if (_current_selection == talk_m)
	{
		std::vector<std::vector<std::string>> vector = {{}};
		act_text = vector;
		cost_round = 0;
	}
}

void Migosp::check_mercy()
{
	if (_current_selection == talk_m)
	{
		_is_mercy = true;
	}
}

std::vector<std::vector<std::string>> Migosp::get_random_text(std::string name)
{
    std::vector< std::vector<std::vector<std::string> >> monster_text;
	if(name == "neutral")
	{
		monster_text ={
			text_content.get_reaction("netral_1"),
			text_content.get_reaction("netral_2"),
			text_content.get_reaction("netral_3"),
			text_content.get_reaction("netral_4"),
			text_content.get_reaction("netral_5"),
			text_content.get_reaction("netral_6"),
			text_content.get_reaction("netral_7"),
			text_content.get_reaction("netral_8"),
			text_content.get_reaction("netral_9"),
			text_content.get_reaction("netral_10"),
			text_content.get_reaction("netral_11")
		};
		int random_num = generate_random_num(0,monster_text.size());
		return monster_text[random_num];
	}
	return {{}};
}

void Migosp::set_monster_frame()
{
	monster_text_vector.clear();
	monster_text_vector.shrink_to_fit();
	//
	 for(unsigned int j=0;j<monster_text[monster_times].size();j++)
	 {
	 	monster_text_vector.push_back(TEXXT_M(monster_text[monster_times][j]));
	 }
	monster_frame_game_text = GameText(monster_text_vector,monster_mode);
	monster_cost_round = monster_text.size();
	monster_frame_mode = no_enter_talk;

	// monster_text = text_content.get_reaction("text","netral_1");
	//  for(unsigned int j=0;j<monster_text[monster_times].size();j++)
	//  {
	//  	monster_text_vector.push_back(TEXXT_M(monster_text[monster_times][j]));
	//  }
	// monster_frame_game_text = GameText(monster_text_vector,monster_mode);
	// monster_cost_round = monster_text.size();
	// monster_frame_mode = enter_talk;
	//enter_talk work example
}

void Migosp::set_next_round_text_updata()
{
	next_text_vector.clear();
	next_text_vector.shrink_to_fit();
	next_round_text = text_content.get_reaction("next_round");
	
	if (hp < 50)
	{
		next_round_text = text_content.get_reaction("hp_low");
	}
	
	 for(unsigned int j=0;j<next_round_text[0].size();j++)
	 {
		   next_text_vector.push_back(TEXXT(next_round_text[0][j]));
	 }
	act_next_round = GameText (next_text_vector,talk_mode);
}

void Migosp::fight_open(Move* heart, Character* charactor)
{
	set_barrage_enable(true);
	get_barrage().damege_hit(heart,charactor);
}

bool Migosp::get_fight_end()
{
	battel_mode_timer += game_framework::CSpecialEffect::GetEllipseTime();
	return (battel_mode_timer >=1300);
}

void Migosp::show_barrage(Move* heart, Character* charactor,int stage)
{
    barrage.show_img();
}

