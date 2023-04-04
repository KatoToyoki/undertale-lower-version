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
                          Items *items,
                          Charactor *charactor)//宣告於OnMove()
{
	_user_frame = user_frame;
	_user_frame->control_frame(to_talk);
	_user_frame->set_choose(false);

	_button_frame = button_frame;
	_button_frame->set_updata_enable(true);

	_monster_frame = monster_frame;
    _monster_frame->set_enable(false);
    _monster_frame->_monster_saying_is_done = true;

	_heart_test = heart_test;
    _heart_test->move_control(_user_frame->get_corner(),false);
    _heart_test->set_show_img_enable(false);
	_heart_test->set_heart_postion(935,698);
	_heart_test->time_count = 1000;

	_game_fight = game_fight;
	_game_fight->set_fight_enable(false);

	_enemy = enemy;
	_enemy->set_act_game_text_enable(false);
	_enemy->check_change_mercy_name_to_yellow_by_is_mercy();

	_items = items;
	_items->set_control_updata(false);
	_items->set_item_cost_round_init(_user_frame->get_current_selection(),_button_frame->get_current_selection());
//s	
	_enemy->set_monster_frame_game_text_enable(false);
	_enemy->set_monster_frame_init(_user_frame->get_current_selection());
	_enemy->set_act_init(last_act_selection);// 這邊set next round 可能只會抓到0
	_enemy->set_enemy_targe_choose_hp_bar(false);
	_enemy->set_barrage_enable(false);
	
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),enter_talk);

	_charactor = charactor;
	_charactor->change_hp(false);
	

	if (_user_frame->get_move_done())
	{
		_user_frame->load_text(_enemy->get_next_round_game_text());
		_user_frame->set_choose(true,_enemy->get_next_round_index(),_enemy->get_next_round_text_len());
	}
}

void ShowNormalMode::end()
{
}

void ShowNormalMode::choose_fight_taget()
{
	_button_frame->set_updata_enable(false);
	
	_user_frame->load_text(_enemy->get_monster_name());
	_user_frame->set_choose(true,0,1);
	_enemy->set_enemy_targe_choose_hp_bar(true);
	
	_game_fight->set_fight_enable(false);
}
void ShowNormalMode::choose_fight()
{
	_user_frame->control_frame(to_talk);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	_enemy->set_enemy_targe_choose_hp_bar(false);
	
	_game_fight->set_fight_enable(true);
	// fight.check();
	_user_frame->set_choose(true,0,1);
    _monster_frame->set_enable(false);
	_enemy->set_monster_frame_init(_user_frame->get_current_selection());
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),_enemy->get_now_monster_frame_mode());

	_enemy->hp = 50;
}

void ShowNormalMode::choose_act_target()
{
	_button_frame->set_updata_enable(false);
	
	_user_frame->load_text(_enemy->get_monster_name());
	_user_frame->set_choose(true,0,1);
}

void ShowNormalMode::choose_act()
{
	
	_user_frame->load_text(_enemy->acts.get_act_name_list());
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
	_enemy->set_act_init(_user_frame->get_current_selection());
	
    _monster_frame->set_enable(false);
	_enemy->set_monster_frame_init(_user_frame->get_current_selection());
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),_enemy->get_now_monster_frame_mode());
	//
	last_act_selection = _user_frame->get_current_selection();	
}

void ShowNormalMode::choose_act_after()
{
	_user_frame->set_choose(false);
	_button_frame->all_button_off();

	_user_frame->load_text(_enemy->get_act_after_game_text());
	_enemy->set_act_game_text_enable(true);
	_user_frame->set_choose(true,_enemy->get_now_act_after_index(),_enemy->get_now_act_after_text_len());
}

void ShowNormalMode::choose_item()
{
	_button_frame->set_updata_enable(false);

	_user_frame->load_text(_items->get_item_list());
	_user_frame->set_choose(true,0,_user_frame->get_text_vector_len());
	_items->set_item_cost_round_init(_user_frame->get_current_selection(),_button_frame->get_current_selection());
	
    _monster_frame->set_enable(false);
	_enemy->set_monster_frame_init(0);//目前蟑螂都一樣所以先設0?
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),_enemy->get_now_monster_frame_mode());
	
	_charactor->change_hp(true,_items->get_selection_heal_num());
}

void ShowNormalMode::choose_item_after()
{
	_enemy->set_monster_frame_game_text_enable(false);
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	
	_user_frame->load_text(_items->get_item_after_game_text());
	_items->set_control_updata(true);
	_user_frame->set_choose(true,_items->get_now_item_after_index(),_items->get_now_item_after_text_len());

	_charactor->change_hp(false);
}

void ShowNormalMode::monster_frame_no_battle()
{
	
}

void ShowNormalMode::monster_frame_battle()
{
    _enemy->set_monster_frame_game_text_enable(true);
    _monster_frame->set_enable(true,_enemy->get_now_monster_frame_after_index(),_enemy->get_now_monster_frame_after_text_len());
}

void ShowNormalMode::choose_mercy()
{
	_user_frame->load_text(_enemy->get_mercy_game_text());
	_user_frame->set_choose(true,0,1);
	
    _monster_frame->set_enable(false);
	_enemy->set_monster_frame_init(0);//目前蟑螂都一樣所以先設0?
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(),_enemy->get_now_monster_frame_mode());
}

void ShowNormalMode::choose_mercy_after()
{
	if (_enemy->is_mercy())
	{
		_user_frame->load_text(_enemy->get_mercy_win_game_text());
		_user_frame->set_choose(true,0,2);
	}
}
