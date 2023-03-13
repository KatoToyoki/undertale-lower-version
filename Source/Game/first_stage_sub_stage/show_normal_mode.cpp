#include "stdafx.h"
#include "show_normal_mode.h"

void ShowNormalMode::init(UserFrame *user_frame)
{
	_user_frame = user_frame;
	_user_frame->load_img();
	_user_frame->create_frame(314,1294,312,563);
	// _user_frame->create_frame(314,415,752,563);
}

void ShowNormalMode::set_frame()
{
	_user_frame->control_frame(to_talk);
}