#include "stdafx.h"
#include "monster_frame.h"
#include "vector"
#include "../Library/gamecore.h"
#include "../Library/gameutil.h"

void MonsterFrame::load_img()
{
  monster_frame_img.LoadBitmapByString({"resources/monster_frame.bmp"},RGB(0,0,0));
  monster_frame_img.SetTopLeft(1190,307);
	// monster_frame_img.LoadBitmapByString({"resources/monster_frame_p.bmp"},RGB(0,0,0));
	// monster_frame_img.SetTopLeft(1129,207);
}

void MonsterFrame::set_monster_frame_img(game_framework::CMovingBitmap img)
{
  monster_frame_img = img;
}


void MonsterFrame::load_game_text_and_mode(GameText game_text,int mode)
{
  _game_text = game_text;
  _mode = mode;
}

void MonsterFrame::set_enable(bool enable)
{
  _enable = enable;
  _game_text.set_enable(enable);
}

void MonsterFrame::show_monster_frame_and_print()
{
  DWORD time_count = game_framework::CSpecialEffect::GetEllipseTime();
  if (_enable && _mode == no_enter_talk)
  {
    _time_count +=time_count;
    if (_time_count <=800)
    {
      monster_frame_img.ShowBitmap();
      _game_text.print();
    }
  }
  else if (_enable && _mode == enter_talk && _monster_saying_is_done)
  {
      monster_frame_img.ShowBitmap();
      _game_text.print();
  }
  else if (_enable && _mode == pass_talk)
  {
    _time_count +=time_count;
  }
  else
  {
    _time_count = 0;
  }
}

