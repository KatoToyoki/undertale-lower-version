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
  if (charactor.get_current_hp() == 0)
  {
    GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
  }
  
  if (stage_go > 0)
  {
    enemy->set_act_updata();
    enemy->set_monster_frame_init();
    items.set_item_updata();
  }
  switch (stage_go)
  {
  case 0:
    if (menu.get_current_stage() == 1) {enemy = &migosp;}
    if (menu.get_current_stage() == 2) {enemy = &greater_dog;}
    if (menu.get_current_stage() == 3) {enemy = &migosp;}
    show_normal_mode.load_data(&user_frame,&gameButtonFrame,&monster_frame,&heart_test,&gameFight,enemy,&items,&charactor);
    break;
  case 1:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    show_normal_mode.init();
    // ===========================================================
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
      if (gameFight.GetDurationMinusHP()<=0)
      {
        stage_go+=2;
      }
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
      if (!enemy->is_mercy()) { stage_go += 1; }
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
      if (enemy->is_game_over() && stage_go < 8)
      {
          stage_go = 8;
      }
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
    
    show_normal_mode.monster_frame_no_battle();
    stage_go+=1;
    break;
  case 6:
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    show_normal_mode.monster_frame_battle();
    
    battel_mode_timer = 0;

    // show_normal_mode.set_heart_mode(heart_blue);
    if (enemy->get_now_monster_frame_mode() == enter_talk)
    {
      stage_go_enable_add = true;
    }
    break;
  case 7:
    //maybe battle mode
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    
    monster_frame._monster_saying_is_done = false;
    user_frame.control_frame(enemy->get_monster_battle_mode());

    user_frame.control_frame(enemy->get_monster_battle_mode());
    heart_test.set_show_img_enable(true);
    if (user_frame.get_move_done())
    {
      monster_frame._monster_saying_is_done = false;
      heart_test.move_control(user_frame.get_corner(),true);
    // to do enemy attack
    // ===========================================================
      if (menu.get_current_stage()== 2)
      {
        greaterDogRound.SelectRound(&heart_test,&charactor,1);
      }
      else if (menu.get_current_stage()== 3)
      {
        papyrusRound.SelectRound(&heart_test,&charactor,20);
        papyrusRound.HPcondition(&heart_test,&charactor);
      }
      else
      {
        enemy->set_barrage_enable(true);
        //enemy->get_barrage().damege_hit(&heart_test,&charactor);
      }
    }
    
    heart_test.move_control(user_frame.get_corner(),true);
    heart_test.set_show_img_enable(true);
  
	  battel_mode_timer += game_framework::CSpecialEffect::GetEllipseTime();
    
    if(greaterDogRound.GetIsAttackEnd())
    {
      stage_go = 1;
    }
    else if(papyrusRound.GetIsAttackEnd())
    {
      stage_go = 1;
    }
    break;
  case 8://before exp&gold
    user_frame.control_frame(to_talk);
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    if (user_frame.get_move_done())
    {
      show_normal_mode.choose_act_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
    }
    break;
  case 9://exp&gold
    user_frame.control_frame(to_talk);
    gameButtonFrame.choose_update(false);
    gameButtonFrame.all_button_off();
    if (user_frame.get_move_done())
    {
      enemy->set_mercy(true);
      show_normal_mode.choose_mercy_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
    }
    break;
  }
  
  if (gameFight.is_hp_zero())
  {
    stage_go = 9;
  }
  show_normal_mode.updata();
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  migosp.set_img();
  migosp.set_barrage();
  greater_dog.set_img();
  //greater_dog.set_barrage();
  
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
  gameFight.set_fight_enable(false);
  gameFight.set_monster(&migosp);

  charactor.set_hp_img();
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
  } else{
    //need OnKeyDown can put here

    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
    gameFight.ToStop(nChar);
    enemy->act_after_stage_control_updata(nChar,&stage_go);
    enemy->monster_frame_stage_control_updata(nChar,&stage_go,&monster_frame);
    items.item_after_stage_control_updata(nChar,&stage_go);
    if (stage_go == 3) {enemy->act_choose_count(nChar);}
    if (stage_go!= 7) {charactor.change_hp_updata(nChar);}
    papyrusRound.ToGetEnterCount(nChar);
  }

  //stage_control
  if ((nChar == VK_RETURN || nChar == 0x5A) && ((enemy->is_mercy() && gameButtonFrame.get_current_selection() ==3 && stage_go == 3) || gameFight.is_hp_zero() || stage_go == 9)) {
    GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
  }
  
  if ((nChar == VK_RETURN || nChar == 0x5A) && !items.is_items_empty() && user_frame.get_move_done() && stage_go_enable_add)
  {
    stage_go+=1;
  }
  if ((nChar == 0x58 || nChar == VK_SHIFT) && stage_go_enable_sub)
  {
    stage_go-=1;
  }
  
  if (stage_go == 1 || stage_go <4 && stage_go >1 && ((nChar == 0x5A || nChar == VK_RETURN) || (nChar == 0x58 || nChar == VK_SHIFT)))
  {
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

    // ===========================================================
    // enemy attack path
    papyrusRound.RevealBarrage();
    papyrusRound.DogAnimation(&heart_test,&charactor);

    greaterDogRound.RevealBarrage();

    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    green_line.ShowBitmap();
    monster_frame.show_monster_frame_and_print();
    
    enemy->show_img();
    //enemy->show_barrage();
    enemy->show_enemy_targe_choose_hp_bar();
    
    gameButtonFrame.show_button();
    gameFight.show_fight_img();
    gameFight.MovingBar();

    charactor.show_charactor_data();

    std::string str = std::to_string(stage_go);
    Text stage(50,str,RGB(255,255,255),600,100,100);
    stage.print();

    greaterDogRound.Test2();
    papyrusRound.Test2();
  }
}