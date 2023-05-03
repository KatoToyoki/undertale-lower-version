#include "stdafx.h"
#include "migosp.h"

#include "barrage.h"

Migosp::Migosp()
{
	set_acts();
	_current_selection = 0;
	monster_name = GameText({
		Text (60, "* Migosp", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_text = GameText({
		Text (60, "* Spare", RGB(255,255,255),500, 465,613)},
		target_mode);
	mercy_win_text = GameText({
		Text (60, "* YOU WON!", RGB(255,255,255),500, 465,613),
		Text (60, "* You earned 0 XP and 3 gold.", RGB(255,255,255),500, 465,613)},
		talk_mode);
	_is_mercy = false;
}
void Migosp::set_img()
{
	set_hp_img();
	enemy_img.LoadBitmapByString({"resources/migosp_0.bmp","resources/migosp_1.bmp"},RGB(0,0,0));
	enemy_img.SetTopLeft(993,316);
	enemy_img.SetAnimation(300,false);
	
	enemy_img_init.LoadBitmapByString({"resources/migosp_0.bmp","resources/migosp_1.bmp"},RGB(0,0,0));
	enemy_img_init.SetTopLeft(993,316);
	enemy_img_init.SetAnimation(300,false);

	enemy_img_damege.LoadBitmapByString({"resources/migosp_hit.bmp"},RGB(0,0,0));
	enemy_img_damege.SetTopLeft(993,316);

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
	Text text0 (60, "* Migosp doesn't have a care", RGB(255,255,255),600, 465,613);
	Text text1 (60, "  in the world.", RGB(255,255,255),600, 465,613);
	act_text_vector = {text0,text1};
	next_round_text = text_content.get_reaction("GreaterDogAct","last_pet_count_1");
	GameText act_next_round = GameText(act_text_vector,talk_mode);

	Act act_check = {
        "check",
		act_next_round,
    };
	Act act_talk = {
        "talk",
		act_next_round,
    };
	vector<Act> act_vecter = {act_check,act_talk};
	acts = Acts (act_vecter) ;
	
}
void Migosp::set_act_updata()
{
	set_next_round_text();
	act_text_vector.clear();
	act_text_vector.shrink_to_fit();
	if (_current_selection == check_m )
	{
		act_text = text_content.get_reaction("MigospAct","check");
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
		data = Text(33, "I DON'T", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "CARE", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_2 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2},monster_mode),
			1,
			{0,2}
		};
		data = Text(33, "HEED THE", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "SWARM", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_3 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2},monster_mode),
			1,
			{0,2}
		};
		data = Text(33, "OBEY THE", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "OVERMIND", RGB(0,0,0),30, 1234,382);
		Text data3 = Text(33, "..", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_4 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2},monster_mode),
			1,
			{0,2}
		};
		data = Text(33, "LEGION!", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "WE ARE", RGB(0,0,0),30, 1234,382);
		data3 = Text(33, "LOGION", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_5 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3},monster_mode),
			1,
			{0,3}
		};
		data = Text(33, "FILTHY", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "SINGLE", RGB(0,0,0),30, 1234,333);
		data3 = Text(33, "MINDER", RGB(0,0,0),30, 1234,382);
		Text data4 = Text(33, "...", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_6 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3,data4},monster_mode),
			1,
			{0,4}
		};
		data = Text(33, "IN", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "UNISOM,", RGB(0,0,0),30, 1234,382);
		data3 = Text(33, "NOW", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_7 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3},monster_mode),
			1,
			{0,3}
		};
		data = Text(33, "Swing", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "your", RGB(0,0,0),30, 1234,333);
		data3 = Text(33, "arms,", RGB(0,0,0),30, 1234,382);
		data4 = Text(33, "baby", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_8 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3,data4},monster_mode),
			1,
			{0,4}
		};
		data = Text(33, "Bein' me", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "is the", RGB(0,0,0),30, 1234,382);
		data3 = Text(33, "best!", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_9 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3},monster_mode),
			1,
			{0,3}
		};
		data = Text(33, "Nothin'", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "like", RGB(0,0,0),30, 1234,333);
		data3 = Text(33, "alone", RGB(0,0,0),30, 1234,382);
		data4 = Text(33, "time!", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_10 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3,data4},monster_mode),
			1,
			{0,4}
		};
		data = Text(33, "La la~", RGB(0,0,0),30, 1234,333);
		data2 = Text(33, "Just be", RGB(0,0,0),30, 1234,382);
		data3 = Text(30, "yourself~", RGB(0,0,0),30, 1234,382);
		MonsterText neutral_11 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data,data2,data3},monster_mode),
			1,
			{0,3}
		};
		data = Text(33, "Hiya~", RGB(0,0,0),30, 1234,333);
		MonsterText neutral_12 = {
			"neutral",
			no_enter_talk,
			0,
			GameText ({data},monster_mode),
			1,
			{0,1}
		};
		
		
		vector<MonsterText> game_text_vector =  {
			neutral_1,
			neutral_2,
			neutral_3,
			neutral_4,
			neutral_5,
			neutral_6,
			neutral_7,
			neutral_8,
			neutral_9,
			neutral_10,
			neutral_11,
			neutral_12
		};
		int random_num = generate_random_num(0,game_text_vector.size());
		return game_text_vector[random_num];
	}
	return MonsterText();
}


void Migosp::set_monster_frame()
{
	MonsterText neutral = get_random_game_text("neutral");
	
	_monster_text_vector = {//這邊跟act selection 跑數量要對
		neutral,
		neutral,
		neutral
	};
}
void Migosp::set_next_round_text()
{
	next_text_vector.clear();
	next_text_vector.shrink_to_fit();
	next_round_text = text_content.get_reaction("MigospAct","next_round");
	
	if (hp < 50)
	{
		next_round_text = text_content.get_reaction("MigospAct","hp_low");
	}
	
	 for(unsigned int j=0;j<next_round_text[0].size();j++)
	 {
		   next_text_vector.push_back(TEXXT(next_round_text[0][j]));
	 }
	act_next_round = GameText (next_text_vector,talk_mode);
}
