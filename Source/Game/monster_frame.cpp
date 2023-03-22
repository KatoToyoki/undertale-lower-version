#include "stdafx.h"
#include "monster_frame.h"
#include "vector"
#include "../Library/gamecore.h"
#include "../Library/gameutil.h"

void MonsterFrame::load_img()
{
  monster_frame_img.LoadBitmapByString({"resources/monster_frame.bmp"},RGB(255,255,255));

	data = Text (33, "Mmm, cha", RGB(0,0,0),30, 1234,333);
	data2 = Text (33, "cha cha!", RGB(0,0,0),30, 1234,382);
}

void MonsterFrame::set_img_position(int x, int y)
{
  monster_frame_img.SetTopLeft(x,y);
}

void MonsterFrame::set_enable(bool enable)
{
  _enable = enable;
  data.set_enable(_enable);
  data2.set_enable(_enable);
}

void MonsterFrame::show_monster_frame_and_print()
{
  DWORD time_count = game_framework::CSpecialEffect::GetEllipseTime();
  if (_enable)
  {
    _time_count +=time_count;
    if (_time_count <=1500)
    {
      monster_frame_img.ShowBitmap();
      data.print();
      data2.print();
    }
  }
  else
  {
    _time_count = 0;
  }
}
