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
  migosp.updata_hp_bar_by_hp();
  switch (stage_go)
  {
  case 1:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    
    show_normal_mode.init(&user_frame,&gameButtonFrame,
      &monster_frame,&heart_test,&gameFight,&migosp,&items,&charactor);
    break;
  case 2:
    stage_go_enable_add = true;
    stage_go_enable_sub = true;
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
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      break;
    case 1:
      show_normal_mode.choose_act();
      stage_go_enable_add = true;
      stage_go_enable_sub = true;
      break;
    case 2:
      show_normal_mode.choose_item_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      break;
    case 3:
      show_normal_mode.choose_mercy_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      if (!migosp.is_mercy()) { stage_go += 1; }
      break;
    }
    
    break;
  case 4:
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
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
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      break;
    case 2:
      stage_go+=1;
      break;
    case 3:
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      stage_go+=1;
      break;
    }
    break;
  case 5:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    items.set_control_updata(false);
	  migosp.set_act_game_text_enable(false);
    user_frame.set_choose(false);
    
    heart_test.set_show_img_enable(true);
    show_normal_mode.monster_frame_no_battle();
    stage_go+=1;
    break;
  case 6:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    show_normal_mode.monster_frame_battle();
    user_frame.control_frame(talk_to_normal_battle);
    heart_test.set_show_img_enable(true);
    
    battel_mode_timer = 0;
    break;
  case 7:
    //maybe battle mode
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    
    monster_frame._monster_saying_is_done = false;
    user_frame.control_frame(talk_to_normal_battle);
    migosp.set_barrage_enable(true);

    charactor.change_hp( (heart_test.time_count>=400)
      ,migosp.get_barrage().damege_hit(&heart_test)*(-1));
    
    heart_test.move_control(user_frame.get_corner(),true);
    heart_test.set_show_img_enable(true);

	  battel_mode_timer += game_framework::CSpecialEffect::GetEllipseTime();
    if (battel_mode_timer >= 1300)
    {
      stage_go = 1;
    }
    break;
  }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  migosp.set_img();
  migosp.set_barrage();
  
  user_frame.load_img();
  user_frame.create_frame(314, 1294, 312, 563);
  heart_test.load_img();
  
  gameButtonFrame.LoadSetIMG();
  gameButtonFrame.SetInit();

  menu.load_img_set_postion();
  
  green_line.LoadBitmapByString({"resources/green_line.bmp"},RGB(255,255,255));
  green_line.SetTopLeft(274,20);

  monster_frame.load_img();
  monster_frame.set_img_position(1190,307);

  gameFight.load_img();
  gameFight.set_fight_img_enable(false);

  charactor.set_hp_img();
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
  if ((nChar == VK_RETURN || nChar == 0x5A) && migosp.is_mercy() && gameButtonFrame.get_current_selection() ==3 && stage_go == 3) {
    GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
  }
  
  if ((nChar == VK_RETURN || nChar == 0x5A) && !items.is_items_empty() && stage_go_enable_add)
  {
    stage_go+=1;
    user_frame._current_selection = 0;
    if (stage_go == 8)
    {
      stage_go = 1;
    }
  }
  if ((nChar == 0x58 || nChar == VK_SHIFT) && stage_go_enable_sub)
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

    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    green_line.ShowBitmap();
    monster_frame.show_monster_frame_and_print();
    
    migosp.show_img();
    migosp.show_enemy_targe_choose_hp_bar();
    migosp.show_barrage();
    
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
