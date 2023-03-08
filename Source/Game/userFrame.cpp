#include "stdafx.h"
#include "userFrame.h"
#include "../Library/gamecore.h"

void UserFrame::lord_img()
{
	left_vertical_frame.LoadBitmapByString({"resources/left_vertical_frame.bmp"});
	right_vertical_frame.LoadBitmapByString({"resources/right_vertical_frame.bmp"});
	up_horizontal_frame.LoadBitmapByString({ "resources/horizontal_frame.bmp" });
	down_horizontal_frame.LoadBitmapByString({ "resources/horizontal_frame.bmp" });
}

void UserFrame::move_frame_to_battle_mode()
{
	// game_framework::CSpecialEffect::Delay(1);
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	if (width > battle_frame_size.width)
	{
		create_frame(height,width-16,leftTop.x+8,leftTop.y);
	}
}
void UserFrame::move_frame_to_talk_mode()
{
	// game_framework::CSpecialEffect::Delay(1);
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	if (width < user_frame_size.width)
	{
		create_frame(height,width+16,leftTop.x-8,leftTop.y);
	}
	
}
