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
  charactor.updata_hp_bar_by_hp();
  switch (stage_go)
  {
  case 1:
    show_normal_mode.init(&user_frame,&gameButtonFrame,
      &monster_frame,&heart_test,&gameFight,&migosp,&items,&charactor);
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
      show_normal_mode.choose_item_after();
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
      // show_normal_mode.choose_item_after();
      stage_go+=1;
      break;
    case 3:
      show_normal_mode.choose_mercy();
      break;
    }
    break;
  case 5:
    items.set_control_updata(false);
	  migosp.set_act_game_text_enable(false);
    user_frame.set_choose(false);
    
    show_normal_mode.monster_frame_no_battle();
    stage_go+=1;
    break;
  case 6:
    show_normal_mode.monster_frame_battle();
    user_frame.control_frame(talk_to_papyrus_normal_battle);
    break;
  case 7:
    //maybe battle mode
    
    monster_frame._monster_saying_is_done = false;
    user_frame.control_frame(talk_to_papyrus_normal_battle);
    barrage.set_show_enable(true);
    barrage.damege_hit(&heart_test);
    barrage.right_move(1);
    
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
  barrage = Barrage(2,blue);
  barrage.load_img("enter");
  barrage.set_positon(700,700);
  // game_framework::CSpecialEffect::SetCurrentTime();
  green_line.LoadBitmapByString({"resources/green_line.bmp"},RGB(255,255,255));
  green_line.SetTopLeft(274,20);

  monster_frame.load_img();
  monster_frame.set_img_position(1190,307);

  // monster_frame.load_game_text_and_mode(migosp.get_monster_frame_game_text());

  gameFight.load_img();
  gameFight.set_fight_img_enable(false);

  charactor.set_hp_img();
  migosp.set_img();

}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
  } else{
    //need OnKeyDown can put here no any if else

    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
    gameFight.ToStop(nChar);
    migosp.act_after_stage_control_updata(nChar,&stage_go);
    migosp.monster_frame_stage_control_updata(nChar,&stage_go,&monster_frame);
    items.item_after_stage_control_updata(nChar,&stage_go);
    charactor.change_hp_updata(nChar);
  }
  
  //stage_control don't touch here
  if ((nChar == VK_RETURN || nChar == 0x5A) && !items.is_items_empty())
  {
    stage_go+=1;
    user_frame._current_selection = 0;
  }
  if ((nChar == 0x58 || nChar == VK_SHIFT) && stage_go !=1)
  {
    stage_go-=1;
    user_frame._current_selection = 0;
  }
  //go init
  if (nChar == 0x51)
  {
    stage_go = 1;
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
    heart_test.show_heart_img();

    barrage.show_img();
    
    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    green_line.ShowBitmap();
    monster_frame.show_monster_frame_and_print();
    
    migosp.show_img();
    
    gameButtonFrame.show_button();
    gameFight.show_fight_img();
    gameFight.MovingBar();

    charactor.show_charactor_data();

    std::string str = std::to_string(stage_go);
    Text stage(50,str,RGB(255,255,255),600,100,100);
    stage.set_enable(true);
    stage.print();
    
  }
}
