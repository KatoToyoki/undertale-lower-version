#include "stdafx.h"
#include "game_manager.h"
#include "ButtonFrame.h"
#include "acts.h"
#include "migosp.h"
#include "monster_frame.h"


void GameManager::load_data(UserFrame* user_frame, ButtonFrame* button_frame, MonsterFrame* monster_frame, Move* heart_test, Fight* game_fight, Enemy* enemy, Items* items, Character* charactor)
{
	_user_frame = user_frame;
	_button_frame = button_frame;
	_monster_frame = monster_frame;
	_heart_test = heart_test;
	_game_fight = game_fight;
	_enemy = enemy;
	_items = items;
	_charactor = charactor;
	
	_game_fight->set_monster(enemy);
    _game_fight->load_img();
}

void GameManager::updata()
{
  _charactor->updata_hp_bar_by_hp();
  _enemy->updata_hp_bar_by_hp();
	_enemy ->enemy_shark();
	_user_frame->up_frame_updata(_heart_test);

  if (_button_frame->get_current_selection() != 2)
  {
    _enemy->set_act_init(_user_frame->get_current_selection());
  	_items->set_item_cost_round_init(0,_button_frame->get_current_selection());
  }
  else
  {
  	_items->set_item_cost_round_init(_user_frame->get_current_selection(),_button_frame->get_current_selection());
  }
}

void GameManager::init()//宣告於OnMove()
{
	_user_frame->load_text(_enemy->get_next_round_game_text());
	_user_frame->control_frame(to_talk);
	_user_frame->set_choose(false);
	_user_frame->_current_selection = 0;

	_button_frame->set_updata_enable(true);

    _heart_test->move_control(_user_frame->get_corner(),false);
    _heart_test->set_show_img_enable(false);
	_heart_test->set_heart_postion(935,698);
	_heart_test->shine_time_count = 1000;
	_heart_test->set_shine_mode(false);
	_heart_test->set_heart_jump_enable_and_init(false);

	_game_fight->set_fight_enable(false);

	_enemy->set_act_game_text_enable(false);
	_enemy->check_change_mercy_name_to_yellow_by_is_mercy();
	_enemy->init_barrage_data();//here init round SetAllData 
    _enemy->set_battle_timer(0);

	_items->set_control_updata(false);
	_items->check_and_del_item();
	
	_enemy->set_enemy_targe_choose_hp_bar(false);
	_enemy->set_barrage_enable(false);
	_enemy->hp = _game_fight->get_current_monster_hp();
	
	_charactor->change_hp(false);
	
	if (_user_frame->get_move_done())
	{
		_user_frame->set_choose(true);
	}
}

void GameManager::end()
{
}

void GameManager::choose_fight_taget()
{
	_button_frame->set_updata_enable(false);
	
	_user_frame->load_text(_enemy->get_monster_name());
	_user_frame->set_choose(true);
	_enemy->set_enemy_targe_choose_hp_bar(true);
}
void GameManager::choose_fight()
{
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	_enemy->set_enemy_targe_choose_hp_bar(false);
	
	_game_fight->set_fight_enable(true);
	_user_frame->set_choose(true);
}

void GameManager::choose_act_target()
{
	_button_frame->set_updata_enable(false);
	
	_user_frame->load_text(_enemy->get_monster_name());
	_user_frame->set_choose(true);
}

void GameManager::choose_act()
{
	_user_frame->load_text(_enemy->acts.get_act_name_list());
	_user_frame->set_choose(true);
}

void GameManager::choose_act_after()
{
	_user_frame->set_choose(false);
	_button_frame->all_button_off();

	_user_frame->load_text(_enemy->get_act_after_game_text());
	_enemy->set_act_game_text_enable(true);
	_user_frame->set_choose(true);
}

void GameManager::choose_item()
{
	_button_frame->set_updata_enable(false);

	_user_frame->load_text(_items->get_item_list());
	_user_frame->set_choose(true);

	_charactor->change_hp(true,_items->get_selection_heal_num());
}

void GameManager::choose_item_after()
{
	_user_frame->set_choose(false);
	_button_frame->all_button_off();
	
	_user_frame->load_text(_items->get_item_after_game_text());
	_items->set_control_updata(true);
	_user_frame->set_choose(true);

	_charactor->change_hp(false);
}

void GameManager::monster_frame_no_battle()
{
    _game_fight->set_fight_enable(false);
    _items->set_control_updata(false);
	_user_frame->set_choose(false);
    _enemy->set_enemy_img_init_or_damege(init_img);
}

void GameManager::monster_frame_battle()
{
    _heart_test->set_show_img_enable(true);
    _heart_test->set_shine_mode(false);
    _user_frame->control_frame(_enemy->get_monster_battle_mode());
    _enemy->set_monster_frame_game_text_enable(true);
	_enemy->check_pass(BEFORE_BATTLE);
	
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(BEFORE_BATTLE),_enemy->get_now_monster_frame_mode(BEFORE_BATTLE));
    _monster_frame->set_enable(true);
}

void GameManager::choose_mercy()
{
	_user_frame->load_text(_enemy->get_mercy_game_text());
	_user_frame->set_choose(true);
}

void GameManager::choose_mercy_after()
{
	if (_enemy->is_mercy())
	{
		_user_frame->load_text(_enemy->get_mercy_win_game_text());
		_user_frame->set_choose(true);
	}
}

void GameManager::battle_after_monster_frame()
{
    _enemy->set_monster_frame_game_text_enable(true);
	_enemy->check_pass(AFTER_BATTLE);
	
	_monster_frame->load_game_text_and_mode(_enemy->get_monster_frame_game_text(AFTER_BATTLE),_enemy->get_now_monster_frame_mode(AFTER_BATTLE));
    _monster_frame->set_enable(true);
}

void GameManager::set_heart_mode(HeartMode mode)
{
    _heart_test->set_heart_mode(mode);
    _button_frame->set_heart_mode(mode);
    _user_frame->set_heart_mode(mode);
}
