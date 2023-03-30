#include "stdafx.h"
#include "charactor.h"

void Charactor::set_hp_img()
{
  hp_bar.LoadBitmapByString({"resources/hp_bar.bmp"});
  hp_bar_red.LoadBitmapByString({"resources/hp_bar_red.bmp"});
  hp_bar_black.LoadBitmapByString({"resources/hp_bar_black.bmp"});
}

void Charactor::show_charactor_data()
{
  Text name_text(20,name,RGB(255,255,255),600,311,908);
  Text LV(20,"LV " + std::to_string(level),RGB(255,255,255),600,514,908);
  Text HP(15,"HP",RGB(255,255,255),600,791,913);
  Text HP_num(15,std::to_string(hp)+"/"+std::to_string(hp_max),RGB(255,255,255),600,948,908);

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

