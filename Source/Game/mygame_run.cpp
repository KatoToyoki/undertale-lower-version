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
  user_frame.control_frame(talk_to_long_battle);
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  // all the material here
  user_frame.load_img();
  user_frame.create_frame(314, 1294, 312, 563);
  // user_frame.create_frame(314,416,751,563);
  heart_test.load_img();
  
  gameButtonFrame.LoadSetIMG();
  gameButtonFrame.SetInit();

  menu.load_img_set_postion();
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
      menu.MenuOff();
      // gameButtonFrame.set_updata_enable(true);
    }
  } else{
    gameButtonFrame.choose_update(nChar);
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
    menu.WholeMenu(currentStage);
  } else {
    heart_test.heart.ShowBitmap();

    user_frame.show_frame();
    gameButtonFrame.show_button();
  }
}
