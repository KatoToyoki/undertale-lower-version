#include "stdafx.h"
#include "enemy.h"

int Enemy::generate_random_num(int min, int max)
{
    return ( rand() % ((max-1) - min + 1) + min );
}

void Enemy::show_img()
{
	enemy_img.ShowBitmap();
	if (end_fight)
	{
		enemy_img_end_effc.ShowBitmap();
	}
}

void Enemy::set_enemy_targe_choose_hp_bar(bool enable)
{
	_choose_targe_hp_bar_enable = enable;
}

void Enemy::set_enemy_shark_time(float time)
{
	shark_time = time;
}

void Enemy::enemy_shark()
{
	if (shark_time > 0 )
	{
		shark_time -= 1.0f;
		int x = (int) (enemy_x + sin(shark_time) * 10.0f);
		int y =(int) (enemy_y + sin(shark_time) * 10.0f);
		enemy_img.SetTopLeft(x,y);
	}
	if (shark_time <= 0 )
	{
		enemy_img.SetTopLeft(enemy_x,enemy_y);
	}
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
		enemy_img = enemy_last;
	}
	if (index == damege)
	{
		enemy_img = enemy_img_damege;
	}
	if (index == end_img)
	{
		enemy_img = enemy_img_end;
		end_fight = true;
	}
}

void Enemy::set_barrage_enable(bool enable)
{
    barrage.set_show_enable(enable);
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
		if (cost_round == 0)
		{
			_is_pass_stage = true;
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

void Enemy::act_after_stage_control_updata(UINT nChar)//更改mercy目前在這裡但之後可稜會修?
{
	stage_stop = false;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _act_after_enable)
	{
		if (act_times < cost_round-1)
		{
			act_times+=1;
			stage_stop = true;
		}
	}
}

GameText Enemy::get_act_after_game_text()
{
	return act_after;
}

void Enemy::set_monster_frame_init()
{
	if (!_monster_frame_enable)
	{
		monster_times = 0;
		monster_text = get_random_text("neutral");//only random use need have neutral in json
	}
	set_monster_frame();
}

GameText Enemy::get_monster_frame_game_text()
{
	return monster_frame_game_text;
}

int Enemy::get_now_monster_frame_mode()
{
    return monster_frame_mode;
}

void Enemy::monster_frame_stage_control_updata(UINT nChar, MonsterFrame *monster_frame)
{
	_monster_frame = monster_frame;
	_monster_frame->set_monster_frame_img(monster_frame_img);
	if ((nChar == VK_RETURN || nChar == 0x5A) && _monster_frame_enable )
	{
		if (monster_times < monster_cost_round-1)
		{
			monster_times+=1;
			stage_stop = true;
		}
	}
}

void Enemy::set_monster_frame_game_text_enable(bool enable)
{
	_monster_frame_enable = enable;
	_is_pass_stage = false;
	if (_monster_frame_enable)
	{
		if (monster_frame_mode == no_enter_talk && _monster_frame->_time_count > 800)
		{
			_is_pass_stage = true;
		}
		if(monster_frame_mode == pass_talk && _monster_frame->_time_count > 0)
		{
			_is_pass_stage = true;
		}
	}
}

GameText Enemy::get_next_round_game_text()
{
	return act_next_round;
}

GameText Enemy::set_vector_vector_to_game_text(std::vector<std::vector<std::string>> text,int times,mode mode)
{
	std::vector<Text> temp_text_vector;
	 for(unsigned int j=0;j<text[times].size();j++)
	 {
	 	if (mode == monster_mode_1 || mode == monster_mode_2){ temp_text_vector.push_back(TEXXT_M(text[times][j])); }
	    else { temp_text_vector.push_back(TEXXT(text[times][j])); }
	 }
	return GameText (temp_text_vector,mode);
}
