#include "stdafx.h"
#include "user_frame.h"
#include "../Library/gamecore.h"
#include "game_text.h"
#include "../Library/audio.h"

void UserFrame::load_img() {
  left_vertical_frame.LoadBitmapByString({"resources/left_vertical_frame.bmp"});
  right_vertical_frame.LoadBitmapByString(
      {"resources/right_vertical_frame.bmp"});
  up_horizontal_frame.LoadBitmapByString({"resources/horizontal_frame.bmp"});
  down_horizontal_frame.LoadBitmapByString({"resources/horizontal_frame_down.bmp"});
  down_black.LoadBitmapByString({"resources/down_black.bmp"});
  stage_in_top_black.LoadBitmapByString({"resources/stage_in_top_black.bmp"});
  
  heart.LoadBitmapByString({"resources/heart.bmp","resources/heart_blue.bmp"},RGB(255,255,255));
  heart.SetTopLeft(1000,700);
}

void UserFrame::move_frame_to_battle_mode() {
  int height = get_height();
  int width = get_width();
  Coordinate leftTop = {get_corner()._leftTop.x - get_pixel(),
                        get_corner()._leftTop.y - get_pixel()};
  create_frame(height, width - 40, leftTop.x + 20, leftTop.y);
}
void UserFrame::move_frame_to_talk_mode() {
  int height = get_height();
  int width = get_width();
  Coordinate leftTop = {get_corner()._leftTop.x - get_pixel(),
                        get_corner()._leftTop.y - get_pixel()};
  create_frame(height, width + 40, leftTop.x - 20, leftTop.y);
}

void UserFrame::move_frame_horizontal_down() {
  int height = get_height();
  int width = get_width();
  Coordinate leftTop = {get_corner()._leftTop.x - get_pixel(),
                        get_corner()._leftTop.y - get_pixel()};
  create_frame(height - 10, width, leftTop.x, leftTop.y + 10);
}

void UserFrame::move_frame_horizontal_up() {
  int height = get_height();
  int width = get_width();
  Coordinate leftTop = {get_corner()._leftTop.x - get_pixel(),
                        get_corner()._leftTop.y - get_pixel()};
  create_frame(height + 10, width, leftTop.x, leftTop.y - 10);
}

void UserFrame::change_frame_sub_width() {
  if (get_width() > 416) {
    move_frame_to_battle_mode();
  }
}
void UserFrame::change_frame_down() {
  if (get_height() > 227) {
    move_frame_horizontal_down();
  }
}
void UserFrame::change_frame_add_width() {
  if (get_width() < 1294) {
    move_frame_to_talk_mode();
  }
}
void UserFrame::change_frame_up() {
  if (get_height() < 314) {
    move_frame_horizontal_up();
  }
}

void UserFrame::control_frame(
    frame_command frame_command_control) // change move_done to 判斷 move_done=ture can go
{
  int frame_commend = STOP;
  switch (frame_command_control) {
  case talk_to_normal_battle: // change talk to normal battle
    frame_commend = SUB_WIDTH;
    if (get_width() <= 416) {
      frame_commend = STOP;
      create_frame(314, 416, 751, 563);
      move_done = true;
      break;
    }
    move_done = false;
    break;
  case talk_to_long_battle: // change talk to long battle
    frame_commend = SUB_WIDTH;
    if (get_width() <= 558 && frame_commend == 0) {
      frame_commend = DOWN;
    }
    if (get_height() <= 227 && get_width() <= 558 && frame_commend == 1) {
      create_frame(227, 528, 695, 650);
      frame_commend = STOP;
      move_done = true;
      break;
    }
    move_done = false;
    break;
  case to_talk: // change long battle to talk
    frame_commend = ADD_WIDTH;
    if (get_width() >= 1294-10) {
      frame_commend = UP;
      if (get_height() == 227)
      {
        create_frame(228, 1294, 312, 649);
      }
    }
    if (get_height() >= 314 && get_width() >= 1294) {
      frame_commend = STOP;
      move_done = true;
      create_frame(314, 1294, 312, 563);
      break;
    }
    move_done = false;
    break;
  case talk_to_papyrus_normal_battle:
    frame_commend = SUB_WIDTH;
    if (get_width() <= 575) {
      frame_commend = STOP;
      move_done = true;
      create_frame(314, 575, 671, 563);
      break;
    }
    move_done = false;
    break;
    
  default:
    frame_commend = STOP;
    move_done = true;
    break;
  }
  check_which_change_frame_need_call(frame_commend);
}

void UserFrame::check_which_change_frame_need_call(int frame_commend) {
  if (frame_commend == SUB_WIDTH) {
    change_frame_sub_width();
  } else if (frame_commend == DOWN) {
    change_frame_down();
  } else if (frame_commend == ADD_WIDTH) {
    change_frame_add_width();
  } else if (frame_commend == UP) {
    change_frame_up();
  }
}

void UserFrame::load_text(GameText game_text)
{
  _game_text = game_text;
}

int UserFrame::get_current_selection()
{
  return _current_selection;
}

void UserFrame::set_choose(bool enable)
{
  _enable = enable;
  _game_text.set_enable(_enable);
  if (_enable && _game_text._mode != talk_mode)
  {
    int x= _game_text.get_positon_x(_current_selection);
    int y= _game_text.get_positon_y(_current_selection);
    heart.SetTopLeft(x-78,y+21);
  }
}

void UserFrame::print()
{
  if (_enable){
    _game_text.print();
  }
}

void UserFrame::choose_updata(UINT nChar)
{
  if (_enable)
  {
    if (_game_text._mode == act_item_mode)
    {
      if ( nChar == VK_LEFT && (_current_selection%2) != 0)
      {
        _current_selection -=1;
        game_framework::CAudio::Instance() -> Play(6);
      }
      if (nChar == VK_RIGHT && (_current_selection%2) != 1 && _current_selection+1 <=_game_text.get_vector_len()-1)
      {
        _current_selection +=1;
        game_framework::CAudio::Instance() -> Play(6);
      }
      if (nChar == VK_DOWN && (_current_selection+2<=_game_text.get_vector_len()-1))
      {
        _current_selection +=2;
        game_framework::CAudio::Instance() -> Play(6);
      }
      if (nChar == VK_UP && (_current_selection/2) != 0)
      {
        _current_selection -=2;
        game_framework::CAudio::Instance() -> Play(6);
      }
    }
    if (_game_text._mode == target_mode)
    {
      if (nChar == VK_DOWN && _current_selection < _game_text.get_vector_len()-1)
      {
        _current_selection +=1;
        game_framework::CAudio::Instance() -> Play(6);
      }
      if (nChar == VK_UP && _current_selection != 0)
      {
        _current_selection -=1;
        game_framework::CAudio::Instance() -> Play(6);
      }
    }
  }
}

int UserFrame::get_text_vector_len()
{
  return _game_text.get_vector_len();
}

void UserFrame::show_select_heart()
{
  if (_enable && _game_text._mode != talk_mode)
  {
    heart.ShowBitmap();
  }
}

void UserFrame::set_heart_mode(int mode)
{
  heart.SetFrameIndexOfBitmap(mode);
}


