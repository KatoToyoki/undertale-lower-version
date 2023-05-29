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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	GotoGameState(GAME_STATE_OVER);
	if ( GetKeyState(0x51)&0x8000)
	{
		GotoGameState(GAME_STATE_RUN);
	}
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66, "Initialize...");	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);
	
	game_over.LoadBitmapByString({"resources/gameover.bmp"},RGB(0,0,0));
	game_over.SetTopLeft(497,81);
	heart = Text (60,"Heart!",RGB(255,255,255),100,600,739);
	stay = Text (60,"Stay determined...",RGB(255,255,255),100,600,820);
	press_q = Text (50,"PRESS Q TO EXIT",RGB(255,255,255),100,600,920);
}

void CGameStateOver::OnShow()
{
	
	game_over.ShowBitmap();
	heart.print();
	stay.print();
	press_q.print();
}
