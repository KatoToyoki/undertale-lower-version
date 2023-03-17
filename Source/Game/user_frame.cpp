#include "stdafx.h"
#include "user_frame.h"
#include "../Library/gamecore.h"

void UserFrame::load_img() {
  left_vertical_frame.LoadBitmapByString({"resources/left_vertical_frame.bmp"});
  right_vertical_frame.LoadBitmapByString(
      {"resources/right_vertical_frame.bmp"});
  up_horizontal_frame.LoadBitmapByString({"resources/horizontal_frame.bmp"});
  down_horizontal_frame.LoadBitmapByString({"resources/horizontal_frame.bmp"});
  down_black.LoadBitmapByString({"resources/down_black.bmp"});
}

void UserFrame::move_frame_to_battle_mode() {
  // game_framework::CSpecialEffect::Delay(1);
  int height = get_height();
  int width = get_width();
  Coordinate leftTop = {get_corner()._leftTop.x - get_pixel(),
                        get_corner()._leftTop.y - get_pixel()};
  create_frame(height, width - 40, leftTop.x + 20, leftTop.y);
}
void UserFrame::move_frame_to_talk_mode() {
  // game_framework::CSpecialEffect::Delay(1);
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
void UserFrame::change_talk_to_normal_battle() {
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
    int frame_command_control) // change move_done to 判斷 move_done=ture can go
                               // next act
/*
 * 0 : change talk to normal battle
 * 1 : change talk to long battle
 * 2 : change normal battle to talk
 * 3 : change long battle to talk
 * 4 : idle frame
 */
{
  int frame_commend = 4;
  switch (frame_command_control) {
  case 0: // change talk to normal battle
    frame_commend = 0;
    if (get_width() <= 416) {
      frame_commend = 4;
      create_frame(314, 416, 751, 563);
      break;
    }
    move_done = false;
    break;
  case 1: // change talk to long battle
    frame_commend = 0;
    if (get_width() <= 416) {
      frame_commend = 1;
    }
    if (get_height() <= 227 && get_width() <= 416) {
      frame_commend = 4;
      move_done = true;
      break;
    }
    move_done = false;
    break;
  case 2: // change normal battle to talk
    frame_commend = 2;
    if (get_width() >= 1294) {
      frame_commend = 4;
      move_done = true;
      create_frame(314, 1294, 312, 563);
      break;
    }
    move_done = false;
    break;
  case 3: // change long battle to talk
    frame_commend = 2;
    if (get_width() >= 1294) {
      frame_commend = 3;
    }
    if (get_height() >= 314 && get_width() >= 1294) {
      frame_commend = 4;
      move_done = true;
      create_frame(314, 1294, 312, 563);
      break;
    }
    move_done = false;
    break;
  default:
    frame_commend = 4;
    move_done = true;
    break;
  }
  check_which_change_frame_need_call(frame_commend);
}

void UserFrame::check_which_change_frame_need_call(int frame_commend) {
  if (frame_commend == 0) {
    change_talk_to_normal_battle();
  } else if (frame_commend == 1) {
    change_frame_down();
  } else if (frame_commend == 2) {
    change_frame_add_width();
  } else if (frame_commend == 3) {
    change_frame_up();
  }
}