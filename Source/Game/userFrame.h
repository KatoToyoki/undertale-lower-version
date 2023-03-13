#pragma once
#include "frame.h"

enum frame_command
{
	talk_to_normal_battle,
	talk_to_long_battle,
	no_work,
	to_talk,
	idle
};

class UserFrame : public Frame
{
public:
    void load_img();

	void control_frame(int frame_command_control);

	bool get_move() const { return move_done;}

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

	void set_frame_to_talk();
	
    bool move_done = false;
	
};
