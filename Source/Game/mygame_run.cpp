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
  // user_frame.control_frame(talk_to_long_battle);
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
  gameButtonFrame.set_updata_enable(true);

  menu.load_img_set_postion();

  Text text(45, "*  Check", RGB(255,255,255),750, 465,613);
  Text text1(45, "*  Check1", RGB(255,255,255),750, 465,613);
  Text text2(45, "*  Check2", RGB(255,255,255),750, 465,613);

  std::vector<Text> text_vector = {text,text1,text2,text,text,text};
  game_text = GameText(text_vector,act_mode);
  // game_text.set_enable(true);
  // game_text.set_text_index(0,3);
  user_frame.load_text(game_text);
  user_frame.set_choose(false,0,5);
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
  } else{
    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
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
  if (menu.get_menu()) {
    menu.WholeMenu();
    
  } else {
    heart_test.heart.ShowBitmap();

    user_frame.show_frame();
    user_frame.print();
    gameButtonFrame.show_button();
    game_text.print_vector();
    // game_text.print_text();
  }
}
