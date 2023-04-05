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
    show_normal_mode.init(&user_frame,&gameButtonFrame,
      &monster_frame,&heart_test,&gameFight);
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
    switch (gameButtonFrame.get_current_selection())
    {
    case 0:
      show_normal_mode.choose_fight();
      break;
    case 1:
      show_normal_mode.choose_act();
      break;
    case 2:
      show_normal_mode.choose_item();
      break;
    case 3:
      show_normal_mode.choose_mercy();
      break;
    }
    
    break;
  case 4:
    switch (gameButtonFrame.get_current_selection())
    {
    case 0:
      if (gameFight.GetDurationMinusHP()<=0)
      {
        stage_go+=1;
      }
      break;
    case 1:
      show_normal_mode.choose_act_after();
      break;
    case 2:
      show_normal_mode.choose_item();
      break;
    case 3:
      show_normal_mode.choose_mercy();
      break;
    }
    
    break;
  case 5:
    //maybe battle mode
    
    // to do enemy attack
    boneRed.MovingBarrage(&heart_test,3);
    
    user_frame.set_choose(false);
    user_frame.control_frame(talk_to_papyrus_normal_battle);
    heart_test.move_control(user_frame.get_corner(),true);

    monster_frame.set_enable(true,0,2);
    
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

  // enemy attack path generate
  boneRed.Init();
  boneRed.RandomBarrage();
  
  // game_framework::CSpecialEffect::SetCurrentTime();
  green_line.LoadBitmapByString({"resources/green_line.bmp"},RGB(255,255,255));
  green_line.SetTopLeft(274,20);

  monster_frame.load_img();
  monster_frame.set_img_position(1190,307);
  
	Text data(33, "Mmm, cha", RGB(0,0,0),30, 1234,333);
	Text data2(33, "cha cha!", RGB(0,0,0),30, 1234,382);
  vector<Text> vector = {data,data2};
  GameText game_text(vector,monster_mode);
  monster_frame.load_game_text(game_text);

  gameFight.load_img();
  gameFight.set_fight_enable(false);
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
  } else{
    //need OnKeyDown can put here no any if else

    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
    gameFight.ToStop(nChar);
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

  if(nChar==VK_F1)
  {
    stage_go=1;
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
    heart_test.show_heart_img();

    // enemy attack path
    boneRed.ShowBarrage();
    
    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    green_line.ShowBitmap();
    monster_frame.show_monster_frame_and_print();
    
    gameButtonFrame.show_button();
    gameFight.show_fight_img();
    gameFight.MovingBar();

  }
}
