#include "stdafx.h"
#include "enemy.h"

int Enemy::generate_random_num(int min, int max)
{
    return ( rand() % ((max-1) - min + 1) + min );
}

void Enemy::show_img()
{
	enemy_img.ShowBitmap();
}

void Enemy::set_enemy_targe_choose_hp_bar(bool enable)
{
	_choose_targe_hp_bar_enable = enable;
}

void Enemy::show_enemy_targe_choose_hp_bar()
{
	if (_choose_targe_hp_bar_enable)
	{
		enemy_targe_choose_hp.ShowBitmap();
		enemy_targe_choose_hp_red.ShowBitmap();
		enemy_targe_choose_hp_black.ShowBitmap();
	}
}

void Enemy::set_enemy_img_init_or_damege(int index)
{
	if (index == init_img)
	{
		enemy_img = enemy_img_init;
	}
	if (index == damege)
	{
		enemy_img = enemy_img_damege;
	}
}

void Enemy::set_barrage_enable(bool enable)
{
    barrage.set_show_enable(enable);
}

void Enemy::show_barrage()
{
    barrage.show_img();
}

Barrage Enemy::get_barrage()
{
	return barrage;
}

void Enemy::updata_hp_bar_by_hp()
{
	const float hp_percent = static_cast<float>(hp) / static_cast<float>(hp_max);
	const int hp_bar_percent_width = static_cast<int>(hp_percent * enemy_targe_choose_hp.GetWidth());
	enemy_targe_choose_hp_red.SetTopLeft(hp_bar_x + hp_bar_percent_width,hp_bar_y);
}

void Enemy::check_change_mercy_name_to_yellow_by_is_mercy()
{
	check_mercy();
	if (_is_mercy)
	{
		monster_name._data[0].set_color(RGB(255,255,45));
		mercy_text._data[0].set_color(RGB(255,255,45));
	}
}

void Enemy::set_act_game_text_enable(bool enable)
{
	_act_after_enable = enable;
	if (_act_after_enable )
	{
		Act* act = acts.get_act_by_index(_current_selection);
		if (cost_round == 0)
		{
			*_stege+=1;
		}
	}
}

void Enemy::set_act_init(int current_selection)//monster frame那邊的init有隨機性所以多寫了set去把東西包起來
{
	if(!_act_after_enable)
	{
		act_times = 0;
		_current_selection = current_selection;
	}
}

void Enemy::act_after_stage_control_updata(UINT nChar, int* stage)//更改mercy目前在這裡但之後可稜會修?
{
	_stege = stage;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _act_after_enable)
	{
		if (act_times < cost_round-1)
		{
			act_times+=1;
			*stage-=1;
		}
	}
}

GameText Enemy::get_act_after_game_text()
{
	return act_after;
}

void Enemy::set_monster_frame_init(int current_selection)
{
	if (!_monster_frame_enable)
	{
		monster_times = 0;
		set_monster_frame();
	}
}

GameText Enemy::get_monster_frame_game_text()
{
    return _monster_text_vector[_current_selection].game_text;
}

int Enemy::get_now_monster_frame_after_index()
{
    return _monster_text_vector[_current_selection].index;
}

int Enemy::get_now_monster_frame_after_text_len()
{
    return _monster_text_vector[_current_selection].round_len_list[monster_times+1];
}

int Enemy::get_now_monster_frame_mode()
{
    return _monster_text_vector[_current_selection].mode;
}

void Enemy::monster_frame_stage_control_updata(UINT nChar, int* stage,MonsterFrame *monster_frame)
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

void Enemy::set_monster_frame_game_text_enable(bool enable)
{
	_monster_frame_enable = enable;
	if (_monster_frame_enable)
	{
		MonsterText *monster_text = &_monster_text_vector[_current_selection];
		if (monster_text->mode == no_enter_talk && _monster_frame->_time_count > 800)
		{
			*_stege+=1;
		}
		if(monster_text->mode == pass_talk && _monster_frame->_time_count > 0)
		{
			*_stege+=1;
		}
	}
}

GameText Enemy::get_next_round_game_text()
{
	return act_next_round;
}