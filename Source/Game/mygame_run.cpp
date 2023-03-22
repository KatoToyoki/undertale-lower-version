#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"

#include "../Library/gameutil.h"

#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g) {}

CGameStateRun::~CGameStateRun() {}

void CGameStateRun::OnBeginState() {}
void CGameStateRun::OnMove() // 移動遊戲元素
{
  switch (stage_go)
  {
  case 1:
    show_normal_mode.init(&user_frame,&gameButtonFrame);
    break;
  case 2:
    switch (gameButtonFrame.get_current_selection())
    {
    case 0:
      show_normal_mode.choose_fight_taget();
      break;
    case 1:
      show_normal_mode.choose_act_target();
      break;
    case 2:
      show_normal_mode.choose_item();
      break;
    case 3:
      show_normal_mode.choose_mercy();
      break;
    }
    break;
  case 3:
    show_normal_mode.choose_act();
    break;
  case 4:
    show_normal_mode.choose_act_after();
    break;
  case 5:
    //maybe battle mode
    barrage.set_show_enable(true);
    barrage.damege_hit(&heart_test);
    
    user_frame.set_choose(false);
    user_frame.control_frame(talk_to_papyrus_normal_battle);
    heart_test.move_control(user_frame.get_corner(),true);
    
    break;
  }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  user_frame.load_img();
  user_frame.create_frame(314, 1294, 312, 563);
  heart_test.load_img();
  
  gameButtonFrame.LoadSetIMG();
  gameButtonFrame.SetInit();

  menu.load_img_set_postion();

  barrage.load_img("enter");
  barrage.set_positon(700,700);
  // game_framework::CSpecialEffect::SetCurrentTime();
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
  } else{
    //need OnKeyDown can put here no any if else

    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
    
  }


  
  //stage_control don't touch here
  if (nChar == VK_RETURN || nChar == 0x5A)
  {
    stage_go+=1;
    user_frame._current_selection = 0;
  }
  if ((nChar == 0x58 || nChar == VK_SHIFT) && stage_go !=1)
  {
    stage_go-=1;
    user_frame._current_selection = 0;
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
    //all show thing put here no any if else
    heart_test.show_heard_img();

    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    gameButtonFrame.show_button();

    barrage.show_img();
  }
}
