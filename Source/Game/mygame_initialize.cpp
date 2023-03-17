#include "stdafx.h"
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gamecore.h"
#include "../Library/gameutil.h"
#include "mygame.h"
#include <ddraw.h>
#include <mmsystem.h>

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g) {}

void CGameStateInit::OnInit() {
  //
  // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
  //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
  //
  ShowInitProgress(0, "Start Initialize..."); // 一開始的loading進度為0%
  //
  // 開始載入資料
  //
  Sleep(1000); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
  //
  // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
  //

  title.LoadBitmapByString({"resources/undertale.bmp"});
  title.SetTopLeft(342, 400);
  enterCommand.LoadBitmapByString(
      {"resources/empty_enter.bmp", "resources/enter.bmp"});
  enterCommand.SetTopLeft(815, 700);
}

void CGameStateInit::OnBeginState() {}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if (nChar == VK_RETURN) {
    GotoGameState(GAME_STATE_RUN); // 切換至GAME_STATE_RUN
  }
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {}

void CGameStateInit::OnShow() { StartMenu(); }

void CGameStateInit::StartMenu() {
  title.ShowBitmap();
  Sleep(200);
  enterCommand.ShowBitmap();
  enterCommand.SetAnimation(300, false);
}