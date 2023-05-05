#include "stdafx.h"
#include "menu.h"
#include <ddraw.h>

#include "text.h"

void Menu::load_img_set_postion()
{
  menuTop.LoadBitmapByString({"resources/menu_top.bmp"},RGB(0,0,0));
  menuTop.SetTopLeft(727, 0);
  menuBottom.LoadBitmapByString({"resources/menu_bottom.bmp"},RGB(0,0,0));
  menuBottom.SetTopLeft(607,662);

  stage1 = Text(40,"Stage1",RGB(255,255,255),800,430,480);
  stage2 = Text(40,"Stage2",RGB(255,255,255),800,880,480);
  stage3 = Text(40, "Stage3",RGB(255,255,255),800,1330,480);
  LV_text = Text(40, "LV 1        00:00",RGB(255,255,255),800,834,291);
  //45
}


void Menu::WholeMenu()
{
  ShowMenuImg();
  MenuState();
}

void Menu::MenuState()
{
  switch (current_stage)
  {
  case(1):
    stage1.set_color(RGB(255,255,45));
    stage2.set_color(RGB(255,255,255));
    stage3.set_color(RGB(255,255,255));
    save_point = Text(50, "Ruins-Mouse Hole",RGB(255,255,255),800,555,365);
    
    break;
  case(2):
    stage1.set_color(RGB(255,255,255));
    stage2.set_color(RGB(255,255,45));
    stage3.set_color(RGB(255,255,255));
    save_point = Text(50, "Snowdin-Dog House",RGB(255,255,255),800,555,365);
    break;
  case(3):
    stage1.set_color(RGB(255,255,255));
    stage2.set_color(RGB(255,255,255));
    stage3.set_color(RGB(255,255,45));
    save_point = Text(50, "Snowdin-Town",RGB(255,255,255),800,555,365);
    break;
  }
  stage1.print();
  stage2.print();
  stage3.print();
  LV_text.print();
  save_point.print();
}

void Menu::ShowMenuImg()
{
  menuTop.ShowBitmap();
  menuBottom.ShowBitmap();
}


void Menu::MenuOff()
{
  menuTop.UnshowBitmap();
  menuBottom.UnshowBitmap();
}

void Menu::choose(UINT nChar)
{
  
    if (nChar == VK_LEFT && current_stage != 1) {
      current_stage -= 1;
    } else if (nChar == VK_RIGHT && current_stage != 3) {
      current_stage += 1;
    }

    if (nChar == VK_RETURN || nChar == 0x5A) {
      isMenu = false;
      MenuOff();
      // gameButtonFrame.set_updata_enable(true);
    }
}

bool Menu::get_menu()
{
  return isMenu;
}


