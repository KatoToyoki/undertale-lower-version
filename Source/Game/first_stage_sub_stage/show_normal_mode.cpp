#include "stdafx.h"
#include "show_normal_mode.h"
#include "../ButtonFrame.h"
#include "../acts.h"
#include "../monster_frame.h"

void ShowNormalMode::init(UserFrame *user_frame,
                          ButtonFrame *button_frame,
                          MonsterFrame *monster_frame,
                          Move *heart_test,
                          Fight *game_fight)//宣告於OnMove()
{
	_user_frame = user_frame;
	_user_frame->control_frame(to_talk);

	_button_frame = button_frame;
	_button_frame->set_updata_enable(true);

	_monster_frame = monster_frame;
    _monster_frame->set_enable(false);

	_heart_test = heart_test;
    _heart_test->move_control(_user_frame->get_corner(),false);

	_game_fight = game_fight;
	_game_fight->set_fight_img_enable(false);
	
	// _ememy.print_text(text, true);
	Text text(60, "* Monster_say_someting", RGB(255,255,255),500, 465,613);
	std::vector<Text> text_vector = {text,text,text,text};
	GameText game_text = GameText(text_vector,talk_mode);
	_user_frame->load_text(game_text);
	_user_frame->set_choose(true,0,3);
	
}

void ShowNormalMode::end()
{
}

void ShowNormalMode::choose_fight_taget()
{
	_button_frame->set_updata_enable(false);
	// _ememy.print_saying(???,false);
	
	// _enemy.name_print(true);
	// _enemy.life_print(true);
	_user_frame->set_choose(true,0,1);
	
	// _game_fight->set_fight_img_enable(true);
}
void ShowNormalMode::choose_fight()
{
	// _enemy.name_print(false);
	// _enemy.life_print(false);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	
	// fight.check();
	_user_frame->set_choose(true,0,1);
}

void ShowNormalMode::choose_act_target()
{
	// _ememy.print_saying(???,false);
	_button_frame->set_updata_enable(false);
	
	// _enemy.name_print(true);
	
	Text text(60, "* target", RGB(255,255,255),500, 465,613);
	std::vector<Text> text_vector = {text,text,text};
	GameText game_text = GameText(text_vector,target_mode);
	
	_user_frame->load_text(game_text);
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
}

void ShowNormalMode::choose_act()
{
	// _enemy.name_print(false);
	
	// _enemy.print_act_vector_text(true);
	
	Text text(60, "* act", RGB(255,255,255),500, 465,613);
	std::vector<Text> text_vector = {text,text,text,text};
	GameText game_text = GameText(text_vector,act_item_mode);
	
	_user_frame->load_text(game_text);
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
}

void ShowNormalMode::choose_act_after()
{
	_user_frame->set_choose(false);
	// _enemy.print_act_vector_text(false);
	_button_frame->all_button_off();

	// _enemy.print_select_act_text(true);
	Text text0(60, "* Migosp - AT 7 DF 5", RGB(255,255,255),600, 465,613);
	Text text1(60, "* It seems evil,but it's just ", RGB(255,255,255),600, 465,613);
	Text text2(60, "  with the wrong crowd...", RGB(255,255,255),600, 465,613);
	std::vector<Text> text_vector = {text0,text1,text2};
	GameText game_text = GameText(text_vector,talk_mode);
	_user_frame->load_text(game_text);
	_user_frame->set_choose(true,0,3);
}

void ShowNormalMode::choose_item()
{
	_button_frame->set_updata_enable(false);
	// _ememy.print_saying(???,false);

	// _item.print_item_vecter(true);
	// _item.choose_updata(true);
}

