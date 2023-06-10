#pragma once
#include "frame.h"
#include "game_text.h"

enum frame_command_c {
  talk_to_normal_battle,
  talk_to_long_battle,
  to_talk,
  idle,
  talk_to_papyrus_normal_battle,
  papyrus_normal_to_bit_bone_dog,
  bit_bone_dog_to_papyrus_normal
};

enum frame_act
{
  SUB_WIDTH,
  DOWN,
  ADD_WIDTH,
  UP,
  ADD_RIGHT_WIDTH,
  SUB_RIGHT_WIDTH,
  STOP
};

class UserFrame : public Frame {
public:
  UserFrame() = default;
  void load_img();
  void show_select_heart();

  void control_frame(frame_command_c frame_command_control);

  bool get_move_done() const { return move_done; }
  int get_current_selection();
  int get_text_vector_len();
  
  void load_text(GameText* game_text);
  void set_choose(bool enable);
  void set_heart_mode(int mode);
  void up_frame_updata(Move *heart);
  
  void choose_updata(UINT nChar);
  void print();
  
  int _current_selection = 0;
  
  game_framework::CMovingBitmap heart;

private:
  void move_frame_sub_width();
  void move_frame_add_width();
  void move_frame_horizontal_down();
  void move_frame_horizontal_up();
  void move_frame_add_right_width();
  void move_frame_sub_right_width();

  void check_which_change_frame_need_call(int frame_commend);
  
  bool move_done = true;
  bool _enable = false;
  bool _up_limit_enable = false;
  GameText *_game_text;
};