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
	monster_text = text_content.get_reaction("neutral");
}

void Migosp::set_img()
{
	set_hp_img();
    enemy_x = 993;
    enemy_y = 316;

	monster_frame_img.LoadBitmapByString({"resources/monster_frame.bmp"},RGB(0,0,0));
	monster_frame_img.SetTopLeft(1190,307);
	
	enemy_img_end_effc.LoadBitmapByString({"resources/enemy_end_effc.bmp"},RGB(0,0,0));
	enemy_img_end_effc.SetTopLeft(enemy_x,enemy_y);
	
	enemy_img_init.LoadBitmapByString({"resources/migosp_0.bmp","resources/migosp_1.bmp"},RGB(0,0,0));
	enemy_img_init.SetTopLeft(enemy_x,enemy_y);
	enemy_img_init.SetAnimation(300,false);

	enemy_img_damege.LoadBitmapByString({"resources/migosp_hit.bmp"},RGB(0,0,0));
	enemy_img_damege.SetTopLeft(enemy_x,enemy_y);

	enemy_img_end.LoadBitmapByString({"resources/migosp_end.bmp"},RGB(0,0,0));
	enemy_img_end.SetTopLeft(enemy_x,enemy_y);

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
	vector<string> act_name_vector = {"check","talk"};
	vector<string> act_vecter = act_name_vector;
	acts = Acts (act_vecter);
}
void Migosp::set_act_text_updata()
{
	std::vector<std::vector<std::string>> act_text = {{}};
	if (_current_selection == CHECK_M )
	{
		act_text = text_content.get_reaction("check");
	}
	act_after = set_vector_vector_to_game_text(act_text,act_times);
	cost_round = act_text.size();
	
	if (_current_selection == TALK_M)
	{
		std::vector<std::vector<std::string>> vector = {{}};
		act_text = vector;
		cost_round = 0;
	}
}

void Migosp::check_mercy()
{
	if (_current_selection == TALK_M)
	{
		_is_mercy = true;
	}
}

void Migosp::set_monster_frame_before()
{
	//
	monster_frame_game_text_before_battle = set_vector_vector_to_game_text(monster_text,monster_times_before,monster_mode_1);
	monster_cost_round_before = monster_text.size();
	monster_frame_mode_before_battle = no_enter_talk;

	// monster_text = text_content.get_reaction("test");
	// monster_frame_game_text_before_battle = set_vector_vector_to_game_text(monster_text,monster_times,monster_mode_1);
	// monster_cost_round_before = monster_text.size();
	// monster_frame_mode_before_battle = enter_talk;
	//enter_talk work example
}

// void Migosp::set_monster_frame_after()
// {
	// monster_text = text_content.get_reaction("test");
	// monster_frame_game_text_after_battle = set_vector_vector_to_game_text(monster_text,monster_times,monster_mode_1);
	// monster_cost_round_after = monster_text.size();
	// monster_frame_mode_after_battle = enter_talk;
// }

void Migosp::set_next_round_text_updata()
{
    std::vector<std::vector<std::string>> next_round_text = {{}};
	next_round_text = text_content.get_reaction("next_round");
	
	if (hp < 50)
	{
		next_round_text = text_content.get_reaction("hp_low");
	}
	
	act_next_round = set_vector_vector_to_game_text(next_round_text,0);
}

void Migosp::fight_open(Move* heart, Character* charactor)
{
	set_barrage_enable(true);
	get_barrage().damege_hit(heart,charactor);
}

bool Migosp::get_fight_end()
{
	battel_mode_timer += (int)game_framework::CSpecialEffect::GetEllipseTime();
	return (battel_mode_timer >=1300);
}

void Migosp::show_barrage(Move* heart, Character* charactor,int stage)
{
    barrage.show_img();
}

frame_command_c Migosp::get_monster_battle_mode()
{
	if (battel_mode_timer >500 && battel_mode_timer<1300)
		return bit_bone_dog_to_papyrus_normal;
	if (battel_mode_timer >100)
		return papyrus_normal_to_bit_bone_dog;
	return talk_to_papyrus_normal_battle;
	
	// return talk_to_normal_battle;
}

void Migosp::act_choose_count(int button_current)
{
	monster_text = text_content.get_reaction("neutral");
}

