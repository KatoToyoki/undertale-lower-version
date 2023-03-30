#include "stdafx.h"
#include "charactor.h"

#include "text.h"

void Charactor::set_hp_img()
{
  hp_bar.LoadBitmapByString({"resources/char_hp.bmp"});
  hp_bar_red.LoadBitmapByString({"resources/char_hp_red.bmp"});
  hp_bar_black.LoadBitmapByString({"resources/char_hp_black.bmp"});

  hp_bar.SetTopLeft(hp_bar_position_x,hp_bar_position_y);
  hp_bar_red.SetTopLeft(max_bar_position_x,hp_bar_position_y);
  hp_bar_black.SetTopLeft(max_bar_position_x,hp_bar_position_y);
}

void Charactor::show_charactor_data()
{
  Text name_text(50,name,RGB(255,255,255),600,311,890);
  Text LV(50,"LV " + std::to_string(level),RGB(255,255,255),600,514,890);
  Text HP(35,"HP",RGB(255,255,255),600,791,898);
  Text HP_num(50,std::to_string(hp)+" / "+std::to_string(hp_max),RGB(255,255,255),600,max_bar_position_x+29,890);

  hp_bar.ShowBitmap();
  hp_bar_red.ShowBitmap();
  hp_bar_black.ShowBitmap();
  
  name_text.set_enable(true);
  name_text.print();
  LV.set_enable(true);
  LV.print();
  HP.set_enable(true);
  HP.print();
  HP_num.set_enable(true);
  HP_num.print();
}

void Charactor::change_hp(int heal_or_damege)
{
  hp += heal_or_damege;
  if (hp > hp_max)
  {
    hp = hp_max;
  }
}

void Charactor::updata_hp_bar_by_hp()
{
  int move_red_bar_position = max_bar_position_x - (one_hp_pixel * (hp_max - hp));
  hp_bar_red.SetTopLeft(move_red_bar_position,hp_bar_position_y);
}
