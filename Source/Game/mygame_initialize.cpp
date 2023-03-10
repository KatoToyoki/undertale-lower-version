#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar==VK_LEFT &&current!=0)
	{
		current-=1;
	}
	else if(nChar==VK_RIGHT&&current!=2)
	{
		 current+=1;
	}
	
	if(nChar==VK_RETURN)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	
}

void CGameStateInit::OnShow()
{
	menuTop.LoadBitmapByString({"resources/menu_top.bmp"});
	menuTop.SetTopLeft(700,0);
	menuTop.ShowBitmap();
	menuBottom.LoadBitmapByString({"resources/menu_bottom.bmp"});
	menuBottom.SetTopLeft(520,560);
	menuBottom.ShowBitmap();

	//anotherTest.push_back(Stage(4,"ddd"));

	switch (current)
	{
	case(0):
		StageButton0ON();
		StageButton1OFF();
		StageButton2OFF();
		break;
	case(1):
		StageButton0OFF();
		StageButton1ON();
		StageButton2OFF();
		break;
	case(2):
		StageButton0OFF();
		StageButton1OFF();
		StageButton2ON();
		break;
	}
	
}

void CGameStateInit::StartMenu()
{
	
}


void CGameStateInit::StageButton0OFF()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
	CTextDraw::Print(pDC, 400, 320, "stage1");
	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::StageButton1OFF()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
	CTextDraw::Print(pDC, 850, 320, "stage2");
	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::StageButton2OFF()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
	CTextDraw::Print(pDC, 1300, 320, "stage3");
	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::StageButton0ON()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
	CTextDraw::Print(pDC, 400, 320, "stage1");
	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::StageButton1ON()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
	CTextDraw::Print(pDC, 850, 320, "stage2");
	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::StageButton2ON()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
	CTextDraw::Print(pDC, 1300, 320, "stage3");
	CDDraw::ReleaseBackCDC();
}
