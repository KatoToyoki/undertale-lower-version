#include "stdafx.h"
#include "show_normal_mode.h"
#include "../monster_frame.h"

void ShowNormalMode::init(UserFrame *user_frame)
{
	_user_frame = user_frame;
	_user_frame->control_frame(to_talk);
}

void ShowNormalMode::show_monster_text()
{
	
		
}
