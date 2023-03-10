#pragma once
#include "frame.h"


class UserFrame : public Frame
{
public:
    void lord_img();

	void control_frame(int frame_commend_control);
    bool move_done = false;

private:
    void move_frame_to_battle_mode();
    void move_frame_to_talk_mode();
    void move_frame_horizontal_down();
    void move_frame_horizontal_up();
	
	void change_talk_to_normal_battle();
	void change_frame_down();
	void change_frame_add_width();
	void change_frame_up();
	void check_which_change_frame_need_call(int frame_commend);
	
};
