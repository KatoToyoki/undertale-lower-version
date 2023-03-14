#include "stdafx.h"
#include "show_normal_mode.h"
#include "../ButtonFrame.h"

void ShowNormalMode::init(UserFrame *user_frame,
	ButtonFrame *button_frame)//宣告於OnMove()
{
	_user_frame = user_frame;
	_user_frame->control_frame(to_talk);

	_button_frame = button_frame;
}

void ShowNormalMode::open_chooes_updata()//宣告於OnKeyDown()
{
	_button_frame->choose_updata();
}

void ShowNormalMode::choose_fight_taget()
{
	
}



