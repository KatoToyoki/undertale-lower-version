/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that
 *they are event driven. 2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 */

#include "stdafx.h"

#include "ButtonFrame.h"
#include "move.h"
#include "user_frame.h"
#include "menu.h"
#include "game_text.h"
#include "first_stage_sub_stage/show_menu.h"
#include "first_stage_sub_stage/show_normal_mode.h"
#include "barrage.h"
#include "Character.h"
#include "monster_frame.h"
#include "Fight.h"
#include "BarrageMode.h"

#include "../Library/audio.h"

// ============================================
#include "papyrus_rounds/RoundX.h"
#include "papyrus_rounds/Round0.h"
#include "papyrus_rounds/Round1.h"
#include "papyrus_rounds/Round2.h"
#include "papyrus_rounds/Round3.h"
#include "papyrus_rounds/Round4.h"
#include "papyrus_rounds/Round5.h"



namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID { // 定義各種音效的編號
  AUDIO_DING,   // 0
  AUDIO_LAKE,   // 1
  AUDIO_NTUT    // 2
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState {
public:
  CGameStateInit(CGame *g);
  void OnInit();                  // 遊戲的初值及圖形設定
  void OnBeginState();            // 設定每次重玩所需的變數
  void OnKeyUp(UINT, UINT, UINT); // 處理鍵盤Up的動作
  void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
  void StartMenu();                              // 開始畫面

protected:
  void OnShow(); // 顯示這個狀態的遊戲畫面
private:
  CMovingBitmap logo; // csie的logo
  /*
   * definition of using material in start menu
   */
  CMovingBitmap title, enterCommand;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState {
public:
  CGameStateRun(CGame *g);
  ~CGameStateRun();
  void OnBeginState(); // 設定每次重玩所需的變數
  void OnInit();       // 遊戲的初值及圖形設定
  void OnKeyDown(UINT, UINT, UINT);
  void OnKeyUp(UINT, UINT, UINT);
  void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
  void OnLButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作
  void OnMouseMove(UINT nFlags, CPoint point);   // 處理滑鼠的動作
  void OnRButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
  void OnRButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作
  

protected:
  void OnMove(); // 移動遊戲元素
  void OnShow(); // 顯示這個狀態的遊戲畫面
private:
  /*
   * the images that game used define here
   */
  UserFrame user_frame;
  ButtonFrame button_frame;
  Move heart_test;
  Menu menu;
  GameText game_text;
  ShowNormalMode show_normal_mode;

  RoundX roundX=RoundX(3);
  Round0 round0=Round0(15);
  Round1 round1=Round1(3);
  Round2 round2=Round2(7);
  Round3 round3=Round3(7);
  Round4 round4=Round4(5);
  Round5 round5=Round5(11);


  MonsterFrame monster_frame;
  Migosp migosp;
  Items items;
  Character charactor;
  
  int stage_go = 0;
  bool stage_go_enable_add = true;
  bool stage_go_enable_sub = true;
  int battel_mode_timer = 0;

  ButtonFrame gameButtonFrame;
  Fight gameFight;

  CMovingBitmap green_line;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState {
public:
  CGameStateOver(CGame *g);
  void OnBeginState(); // 設定每次重玩所需的變數
  void OnInit();

protected:
  void OnMove(); // 移動遊戲元素
  void OnShow(); // 顯示這個狀態的遊戲畫面
private:
  int counter; // 倒數之計數器
  CMovingBitmap game_over;
  Text heart;
  Text stay;
  Text press_q;
};

} // namespace game_framework