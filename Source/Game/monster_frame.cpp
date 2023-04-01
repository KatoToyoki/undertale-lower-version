#include "stdafx.h"
#include "monster_frame.h"
#include "vector"
#include "../Library/gamecore.h"
#include "../Library/gameutil.h"

void MonsterFrame::load_img()
{
  monster_frame_img.LoadBitmapByString({"resources/monster_frame.bmp"},RGB(255,255,255));

}

void MonsterFrame::load_game_text_and_mode(GameText game_text,int mode)
{
  _game_text = game_text;
  _mode = mode;
}


void MonsterFrame::set_img_position(int x, int y)
{
  monster_frame_img.SetTopLeft(x,y);
}

void MonsterFrame::set_enable(bool enable,int head, int text_len)
{
  _enable = enable;
  _game_text.set_enable(enable);
  if (_enable)
  {
    _game_text.set_text_index(head,text_len);
  }
}

void MonsterFrame::show_monster_frame_and_print()
{
  DWORD time_count = game_framework::CSpecialEffect::GetEllipseTime();
  if (_enable && _mode == no_enter_talk)
  {
    _time_count +=time_count;
    if (_time_count <=1500)
    {
      monster_frame_img.ShowBitmap();
      _game_text.print();
    }
  }
  else if (_enable && _mode == enter_talk)
  {
      monster_frame_img.ShowBitmap();
      _game_text.print();
  }
  else
  {
    _time_count = 0;
  }
}
