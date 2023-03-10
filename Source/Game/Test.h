#pragma once
#include <string>

class Test
{
public:
    /*
    CDC *_pDC= game_framework::CDDraw::GetBackCDC();
    ~Test()
    {
        game_framework::CDDraw::ReleaseBackCDC();
    }
    */
    
    int myTest;
    std::string what="ddd";

    Test()
    {
        myTest=333;
    }

};
