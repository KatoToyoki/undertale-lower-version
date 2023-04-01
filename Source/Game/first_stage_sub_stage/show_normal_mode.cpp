#include "stdafx.h"
#include "show_normal_mode.h"
#include "../ButtonFrame.h"
#include "../acts.h"
#include "../migosp.h"
#include "../monster_frame.h"

void ShowNormalMode::init(UserFrame *user_frame,
                          ButtonFrame *button_frame,
                          MonsterFrame *monster_frame,
                          Move *heart_test,
                          Fight *game_fight,
                          Migosp *enemy,
                          Items *items)//宣告於OnMove()
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

	_enemy = enemy;
	_enemy->set_act_game_text_enable(false);

	_items = items;
	_items->set_control_updata(false);
	_items->set_item_cost_round_init(_user_frame->get_current_selection(),_button_frame->get_current_selection());
//s	
	_enemy->set_monster_frame_game_text_enable(false);
	_enemy->set_monster_frame_init(_user_frame->get_current_selection());
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),enter_talk);
	

	if (_user_frame->get_move_done())
	{
		// _ememy.print_text(text, true);
		Text text(60, "* Monster_say_someting", RGB(255,255,255),500, 465,613);
		std::vector<Text> text_vector = {text,text,text,text};
		GameText game_text = GameText(text_vector,talk_mode);
		_user_frame->load_text(game_text);
		_user_frame->set_choose(true,0,3);
	}
}

void ShowNormalMode::end()
{
}

void ShowNormalMode::choose_fight_taget()
{
	_button_frame->set_updata_enable(false);
	// _ememy.print_saying(???,false);
	
	// _enemy.name_print(true);
	Text text(60, "* target", RGB(255,255,255),500, 465,613);
	std::vector<Text> text_vector = {text,text,text};
	GameText game_text = GameText(text_vector,target_mode);
	
	_user_frame->load_text(game_text);
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
	
	// _enemy.life_print(true);
	
	_game_fight->set_fight_img_enable(false);
}
void ShowNormalMode::choose_fight()
{
	// _enemy.name_print(false);
	// _enemy.life_print(false);
	_user_frame->control_frame(to_talk);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	
	_game_fight->set_fight_img_enable(true);//set fight work dont false
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
	
	_user_frame->load_text(_enemy->acts.get_act_name_list());
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
	_enemy->set_act_init(_user_frame->get_current_selection());
	
    _monster_frame->set_enable(false);
	_enemy->set_monster_frame_init(_user_frame->get_current_selection());
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),_enemy->get_now_monster_frame_mode());
	//
}

void ShowNormalMode::choose_act_after()
{
	// _enemy->set_monster_frame_game_text_enable(false);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();

	_user_frame->load_text(_enemy->get_act_after_game_text());
	_enemy->set_act_game_text_enable(true);
	_user_frame->set_choose(true,_enemy->get_now_act_after_index(),_enemy->get_now_act_after_text_len());
}

void ShowNormalMode::choose_item()
{
	_button_frame->set_updata_enable(false);
	// _ememy.print_saying(???,false);

	_user_frame->load_text(_items->get_item_list());
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
	_items->set_item_cost_round_init(_user_frame->get_current_selection(),_button_frame->get_current_selection());
}

void ShowNormalMode::choose_item_after()
{
	_enemy->set_monster_frame_game_text_enable(false);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	
	_user_frame->load_text(_items->get_item_after_game_text());
	_items->set_control_updata(true);
	_user_frame->set_choose(true,_items->get_now_item_after_index(),_items->get_now_item_after_text_len());
}

void ShowNormalMode::monster_frame_no_battle()
{
	
}

void ShowNormalMode::monster_frame_battle()
{
    _enemy->set_monster_frame_game_text_enable(true);
    _monster_frame->set_enable(true,_enemy->get_now_monster_frame_after_index(),_enemy->get_now_monster_frame_after_text_len());
}
