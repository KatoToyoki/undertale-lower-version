#include "stdafx.h"
#include "menu.h"
#include <ddraw.h>

#include "mygame.h"

#include "../Library/gamecore.h"

void Menu::load_img_set_postion()
{
  menuTop.LoadBitmapByString({"resources/menu_top.bmp"});
  menuTop.SetTopLeft(727, 0);
  menuBottom.LoadBitmapByString({"resources/menu_bottom.bmp"});
  menuBottom.SetTopLeft(599, 560);
}


void Menu::WholeMenu(int current_stage)
{
  ShowMenuImg();
  MenuState(current_stage);
}

void Menu::Stage1OFF()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  game_framework::CTextDraw::Print(pDC, 430, 320, "stage1");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::Stage2OFF()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  game_framework::CTextDraw::Print(pDC, 880, 320, "stage2");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::Stage3OFF()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  game_framework::CTextDraw::Print(pDC, 1330, 320, "stage3");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::Stage1ON()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  game_framework::CTextDraw::Print(pDC, 430, 320, "stage1");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::Stage2ON()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  game_framework::CTextDraw::Print(pDC, 880, 320, "stage2");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::Stage3ON()
{
  CDC *pDC = game_framework::CDDraw::GetBackCDC();
  game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  game_framework::CTextDraw::Print(pDC, 1330, 320, "stage3");
  game_framework::CDDraw::ReleaseBackCDC();
}

void Menu::MenuState(int current_stage)
{
  switch (current_stage)
  {
  case(1):
    Stage1ON();
    Stage2OFF();
    Stage3OFF();
    break;
  case(2):
    Stage1OFF();
    Stage2ON();
    Stage3OFF();
    break;
  case(3):
    Stage1OFF();
    Stage2OFF();
    Stage3ON();
    break;
  }
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
