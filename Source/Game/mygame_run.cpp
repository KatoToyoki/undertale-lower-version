#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"

#include "../Library/gameutil.h"

#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>

// #define MID ((1920/2)-(UserFrame.horizontal_up_frame.GetWidth()/2));

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g) {}

CGameStateRun::~CGameStateRun() {}

void CGameStateRun::OnBeginState() {}
void CGameStateRun::OnMove() // 移動遊戲元素
{
  heart_test.move_control(user_frame.get_corner());
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  // all the material here
  user_frame.load_img();
  user_frame.create_frame(314, 1294, 312, 563);
  // user_frame.create_frame(314,416,751,563);
  heart_test.load_img();

  menuTop.LoadBitmapByString({"resources/menu_top.bmp"});
  menuTop.SetTopLeft(727, 0);
  menuBottom.LoadBitmapByString({"resources/menu_bottom.bmp"});
  menuBottom.SetTopLeft(599, 560);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (isMenu) {
    if (nChar == VK_LEFT && currentStage != 1) {
      currentStage -= 1;
    } else if (nChar == VK_RIGHT && currentStage != 3) {
      currentStage += 1;
    }

    if (nChar == VK_RETURN) {
      isMenu = false;
      MenuOff();
      gameButtonFrame.LoadSetIMG();
      gameButtonFrame.SetInit();
    }
  } else if (isMenu == false) {
    gameButtonFrame.choose_update(nChar, nRepCnt, nFlags);
  }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
  
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
  
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
  
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
  
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
  
}
void CGameStateRun::OnShow()
{
  if (isMenu) {
    WholeMenu();
  } else {
    user_frame.show_frame();
    // heart_test.heart.ShowBitmap();

    gameButtonFrame.show_button();
    if (gameButtonFrame.GetIsChange() == true) {
      gameButtonFrame.ChangeState();
    }
  }
}

void CGameStateRun::WholeMenu()
{
  ShowMenuImg();
  MenuState();
}

void CGameStateRun::MenuState()
{
  switch (currentStage)
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

void CGameStateRun::ShowMenuImg()
{
  menuTop.ShowBitmap();
  menuBottom.ShowBitmap();
}

void CGameStateRun::Stage1OFF()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  CTextDraw::Print(pDC, 430, 320, "stage1");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::Stage2OFF()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  CTextDraw::Print(pDC, 880, 320, "stage2");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::Stage3OFF()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
  CTextDraw::Print(pDC, 1330, 320, "stage3");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::Stage1ON()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  CTextDraw::Print(pDC, 430, 320, "stage1");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::Stage2ON()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  CTextDraw::Print(pDC, 880, 320, "stage2");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::Stage3ON()
{
  CDC *pDC = CDDraw::GetBackCDC();
  CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
  CTextDraw::Print(pDC, 1330, 320, "stage3");
  CDDraw::ReleaseBackCDC();
}

void CGameStateRun::MenuOff()
{
  menuTop.UnshowBitmap();
  menuBottom.UnshowBitmap();
}