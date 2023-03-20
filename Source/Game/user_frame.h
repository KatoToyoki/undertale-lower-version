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
  void load_img();

  void control_frame(int frame_command_control);

  bool get_move() const { return move_done; }
  int get_current_selection();
  int get_text_vector_len();
  
  void load_text(GameText game_text);
  void set_choose(bool enable, int head = 0, int text_len = 20);
  
  void choose_updata(UINT nChar);
  void print();
  
  int _current_selection = 0;

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

  void text_color_change();
  
  bool move_done = false;
  bool _enable = false;
  int _head = 0,_text_len = 1;
  GameText _game_text;
};