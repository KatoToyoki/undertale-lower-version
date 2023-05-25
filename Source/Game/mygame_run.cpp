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
    music->Pause();
    music->Play(4,true);
    GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
  }
  
  if (stage_go > LOAD)
  {
	  enemy->set_next_round_text_updata();
    enemy->set_act_text_updata();
	  enemy->set_monster_frame_init();
    enemy->set_monster_frame_game_text_enable(false);
    items.set_item_updata();
    monster_frame.set_enable(false);
  }
  
  switch (stage_go)
  {
  case LOAD:
    if (menu.get_current_stage() == 1) {enemy = &migosp;}
    if (menu.get_current_stage() == 2) {enemy = &greater_dog;}
    if (menu.get_current_stage() == 3) {enemy = &papyrus;}
    game_manager.load_data(&user_frame,&gameButtonFrame,&monster_frame,&heart_test,&gameFight,enemy,&items,&charactor);
    break;
  case INIT:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    game_manager.init();

    break;
  case CHOOSE_TARGET:
    stage_go_enable_add = true;
    stage_go_enable_sub = true;
    switch (gameButtonFrame.get_current_selection())
    {
    case FIGHT:
      game_manager.choose_fight_taget();
      break;
    case ACT:
      game_manager.choose_act_target();
      break;
    case ITEM:
      stage_go = CHOOSE_ACT_ITEM;
      break;
    case MERCY:
      game_manager.choose_mercy();
      break;
    }
    break;
  case CHOOSE_ACT_ITEM:
    stage_go_enable_add = true;
    stage_go_enable_sub = true;
    switch (gameButtonFrame.get_current_selection())
    {
    case FIGHT:
      game_manager.choose_fight();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
      if (gameFight.GetDurationMinusHP()<=0)
        stage_go = SHOW_MONSTER_FRAME_FRAME_STOP;
      break;
    case ACT:
      game_manager.choose_act();
      break;
    case ITEM:
      game_manager.choose_item();
      break;
    case MERCY:
      stage_go = CHOOSE_AFTER;
      break;
    }
    break;
  case CHOOSE_AFTER:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    switch (gameButtonFrame.get_current_selection())
    {
    case FIGHT:
      stage_go_enable_add = false;
      stage_go_enable_sub = false;
      if (gameFight.GetDurationMinusHP()<=0)
        stage_go = SHOW_MONSTER_FRAME_FRAME_STOP;
      break;
    case ACT:
      game_manager.choose_act_after();
      if (enemy->is_game_over() && stage_go < BEFORE_END)
          stage_go = FIGHT_END;
      else if (enemy->_is_pass_stage)
          stage_go = SHOW_MONSTER_FRAME_FRAME_STOP;
      break;
    case ITEM:
      game_manager.choose_item_after();
      break;
    case MERCY:
	    enemy->set_mercy();
      if (!enemy->is_mercy())
        stage_go = SHOW_MONSTER_FRAME_FRAME_STOP;
      else
        stage_go = FIGHT_END;
      break;
    }
    break;
  case SHOW_MONSTER_FRAME_FRAME_STOP:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    
    game_manager.monster_frame_no_battle();
    stage_go = SHOW_MONSTER_FRAME_FRAME_MOVE;
    break;
  case SHOW_MONSTER_FRAME_FRAME_MOVE:
    game_manager.monster_frame_battle();
    if (enemy->_is_pass_stage)
      stage_go = BATTLE;

    // show_normal_mode.set_heart_mode(heart_blue);
    stage_go_enable_add = enemy->get_now_monster_frame_mode(BEFORE_BATTLE) == enter_talk;
    stage_go_enable_sub = false;
    break;
  case BATTLE:
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
   
    user_frame.control_frame(enemy->get_monster_battle_mode());
    heart_test.set_show_img_enable(true);
    
    if (user_frame.get_move_done())
    {
      heart_test.move_control(user_frame.get_corner(),true);
      heart_test.shine_count();
      heart_test.shine_two_second();

      enemy->fight_open(&heart_test,&charactor);
    }
    if (enemy->get_fight_end())
      stage_go = BATTLE_AFTER_MONSTER_FRAME;
    break;
  case BATTLE_AFTER_MONSTER_FRAME:
    stage_go_enable_add = true;
    stage_go_enable_sub = false;
    game_manager.battle_after_monster_frame();
    if (enemy->_is_pass_stage)
      stage_go = BACK_INIT;
    break;
  case BACK_INIT:
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    enemy->act_choose_count(gameButtonFrame.get_current_selection());
    items.set_control_updata(false);
  	enemy->set_act_game_text_enable(false);
    stage_go = INIT;
    break;
  case FIGHT_END:
    if (gameFight.GetDurationMinusHP()<=0 || gameButtonFrame.get_current_selection() != FIGHT)
    {
      music->Play(9);
      enemy->set_enemy_img_init_or_damege(end_img);
      if (enemy->is_game_over() && stage_go < BEFORE_END)
        stage_go = BEFORE_END;
      else
        stage_go = END;
    }
  case BEFORE_END://before exp&gold
    user_frame.control_frame(to_talk);
    stage_go_enable_add = false;
    stage_go_enable_sub = false;
    if (user_frame.get_move_done())
    {
      game_manager.choose_act_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
    }
    break;
  case END://exp&gold
    user_frame.control_frame(to_talk);
    gameButtonFrame.choose_update(false);
    gameButtonFrame.all_button_off();
    if (user_frame.get_move_done())
    {
      enemy->set_mercy(true);
      game_manager.choose_mercy_after();
      stage_go_enable_add = true;
      stage_go_enable_sub = false;
    }
    break;
  }
  
  if (gameFight.is_hp_zero() && stage_go != END)
  {
    stage_go = FIGHT_END;
  }
  game_manager.updata();
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
  migosp.set_img();
  migosp.set_barrage();
  greater_dog.set_img();
  papyrus.set_img();
  
  user_frame.load_img();
  user_frame.create_frame(314, 1294, 312, 563);
  heart_test.load_img();
  
  gameButtonFrame.LoadSetIMG();
  gameButtonFrame.SetInit();

  menu.load_img_set_postion();

  green_line.LoadBitmapByString({"resources/green_line.bmp"},RGB(255,255,255));
  green_line.SetTopLeft(274,20);

  monster_frame.load_img();

  gameFight.set_fight_enable(false);

  charactor.set_hp_img();

  music = CAudio::Instance();
  music ->Load(0,"Resources/Background/start.MP3");
  music ->Load(1,"Resources/Background/01.MP3");
  music ->Load(2,"Resources/Background/02.MP3");
  music ->Load(3,"Resources/Background/03.MP3");
  music ->Load(4,"Resources/Background/end.MP3");
  music ->Load(5,"Resources/Effects/select.MP3");
  music ->Load(6,"Resources/Effects/select_1.MP3");
  music ->Load(7,"Resources/Effects/fight.MP3");
  music ->Load(8,"Resources/Effects/heal.MP3");
  music ->Load(9,"Resources/Effects/endfight.MP3");
  music->Play(0,true);
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (menu.get_menu()) {
    menu.choose(nChar);
    
    ///Music
    if (stage_go == LOAD && (nChar == 0x5A || nChar == VK_RETURN))
    {
      music->Stop(0);
      switch (menu.get_current_stage())
      {
      case 1:
        music->Play(1,true);
        break;
      case 2:
        music->Play(2,true);
        break;
      case 3:
        music->Play(3,true);
        break;
      }
    }
  } else{
    gameButtonFrame.choose_update(nChar);
    user_frame.choose_updata(nChar);
    gameFight.ToStop(nChar);
    enemy->act_after_stage_control_updata(nChar);
    enemy->monster_frame_stage_control_updata(nChar,&monster_frame,stage_go);
    items.item_after_stage_control_updata(nChar);
    if (stage_go!= BATTLE && stage_go!= BATTLE_AFTER_MONSTER_FRAME) {charactor.change_hp_updata(nChar);}
    papyrusRound.ToGetEnterCount(nChar);
  }
  //stage_control
  if ((nChar == VK_RETURN || nChar == 0x5A) && (stage_go == END)) {
    music->Pause();
    music->Play(4,true);
    GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
  }
  
  if ((nChar == VK_RETURN || nChar == 0x5A) && user_frame.get_move_done() && stage_go_enable_add)
  {
    if ((stage_go <= CHOOSE_ACT_ITEM && gameButtonFrame.get_current_selection() != FIGHT)
      || stage_go <= CHOOSE_TARGET)
    {
      music->Play(5);
    }
    if (stage_go == CHOOSE_ACT_ITEM && gameButtonFrame.get_current_selection() == ITEM)
    {
      music->Play(8);
    }
    if (stage_go == INIT && items.is_items_empty())
    {
      music->Play(8);
    }
    else if (!enemy->stage_stop && !items.stage_stop)
    {
      stage_go+=1;
    }
  }
  if ((nChar == 0x58 || nChar == VK_SHIFT) && stage_go_enable_sub)
  {
    if (gameButtonFrame.get_current_selection() == ITEM && stage_go == CHOOSE_ACT_ITEM){ stage_go = INIT;}
    else { stage_go-=1; }
  }
  
  if(stage_go <CHOOSE_AFTER && stage_go > INIT &&
      ((nChar == 0x5A || nChar == VK_RETURN) || (nChar == 0x58 || nChar == VK_SHIFT)))
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
    //all show thing put here
    user_frame.stage_in_top_black.ShowBitmap();
    green_line.ShowBitmap();
    enemy->show_img();
    
    user_frame.up_horizontal_frame.ShowBitmap();
    heart_test.show_heart_img();
    // ===========================================================
    // enemy attack path
    if (user_frame.get_move_done()) {enemy->show_barrage(&heart_test, &charactor,stage_go);}
    if(stage_go==BATTLE)
    {
      if(menu.get_current_stage()==3)
      {
        papyrusRound.SetIsRightTime(true);
        papyrusRound.RevealBarrage();
        papyrusRound.DogAnimation(&heart_test,&charactor);
      }
    }

    user_frame.show_frame();
    user_frame.show_select_heart();
    user_frame.print();//print all thing in user_frame by load_text(GameText) in OnMove and set_enable)
    
    monster_frame.show_monster_frame_and_print();
    
    enemy->show_enemy_targe_choose_hp_bar();
    
    gameButtonFrame.show_button();
    gameFight.show_fight_img();
    gameFight.MovingBar();

    charactor.show_charactor_data();

    std::string str = std::to_string(stage_go);
    Text stage(50,str,RGB(255,255,255),600,100,100);
    stage.print();
  }
}