#include "stdafx.h"
#include "test_text.h"

#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

void test_text::show_test()
{
	
}

void test_text::create_text(TextData data)
{
	CDC *pDC = game_framework::CDDraw::GetBackCDC();

	game_framework::CTextDraw::ChangeFontLog(pDC, data.size, "微軟正黑體", data.color, data.weight);
	text_data_vector.push_back(data);
	game_framework::CTextDraw::Print(pDC, data.x, data.y, data.str);
	game_framework::CDDraw::ReleaseBackCDC();
}

void test_text::change_color(int r,int g,int b, TextData target)
{
	TextData new_text = target;
	new_text.color = RGB(r,g,b);

	create_text(new_text);
}
