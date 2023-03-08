#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>

	// #define MID ((1920/2)-(UserFrame.horizontal_up_frame.GetWidth()/2));

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}
void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (user_frame.get_width()>416 && stage == 0){
		user_frame.move_frame_to_battle_mode();
		if (user_frame.get_width()<416)
		{
			stage = 1;
		}
	}
	else if (stage == 2)
	{
		user_frame.move_frame_to_talk_mode();
		if (user_frame.get_width()>=1294)
		{
			stage = 0;
		}
	}
	else
	{
		Sleep(500);
		stage = 2;
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	// all the material here
	user_frame.lord_img();
	user_frame.create_frame(314,1294,312,563);
	// user_frame.create_frame(314,416,751,563);
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	user_frame.show_frame();
}
