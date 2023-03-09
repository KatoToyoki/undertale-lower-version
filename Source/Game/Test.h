#pragma once
#include "Menu.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
class Test
{
public:
    int myTest;
    Stage testS= Stage(3,"s");
    // CDC *ptr=game_framework::CDDraw::GetBackCDC();
    Test()
    {
        myTest=333;
    }

    int fuck()
    {
        return testS.GetID();
    }
    
    
};
