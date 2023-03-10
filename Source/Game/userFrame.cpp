#include "stdafx.h"
#include "userFrame.h"
#include "../Library/gamecore.h"

void UserFrame::lord_img()
{
	left_vertical_frame.LoadBitmapByString({"resources/left_vertical_frame.bmp"});
	right_vertical_frame.LoadBitmapByString({"resources/right_vertical_frame.bmp"});
	up_horizontal_frame.LoadBitmapByString({ "resources/horizontal_frame.bmp" });
	down_horizontal_frame.LoadBitmapByString({ "resources/horizontal_frame.bmp" });
	down_black.LoadBitmapByString({ "resources/down_black.bmp" });
	
}

void UserFrame::move_frame_to_battle_mode()
{
	// game_framework::CSpecialEffect::Delay(1);
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	create_frame(height,width-40,leftTop.x+20,leftTop.y);
}
void UserFrame::move_frame_to_talk_mode()
{
	// game_framework::CSpecialEffect::Delay(1);
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	create_frame(height,width+40,leftTop.x-20,leftTop.y);
}

void UserFrame::move_frame_horizontal_down()
{
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	create_frame(height-10,width,leftTop.x,leftTop.y+10);
}

void UserFrame::move_frame_horizontal_up()
{
	int height = get_height();
	int width = get_width();
	Coordinate leftTop = {get_corner()._leftTop.x-get_pixel(),get_corner()._leftTop.y-get_pixel()};
	create_frame(height+10,width,leftTop.x,leftTop.y-10);
}
