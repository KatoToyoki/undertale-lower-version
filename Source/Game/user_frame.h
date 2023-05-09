#pragma once
#include "frame.h"
#include "game_text.h"

enum frame_command {
  talk_to_normal_battle,
  talk_to_long_battle,
  no_work,
  to_talk,
  idle,
  talk_to_papyrus_normal_battle
};

class UserFrame : public Frame {
public:
  UserFrame() = default;
  void load_img();
  void show_select_heart();

  void control_frame(int frame_command_control);

  bool get_move_done() const { return move_done; }
  int get_current_selection();
  int get_text_vector_len();
  
  void load_text(GameText game_text);
  void set_choose(bool enable);
  void set_heart_mode(int mode);
  
  void choose_updata(UINT nChar);
  void print();
  
  int _current_selection = 0;
  
  game_framework::CMovingBitmap heart;

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
  
  bool move_done = true;
  bool _enable = false;
  GameText _game_text;
};