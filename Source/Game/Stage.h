#pragma once

#include <string>
#include <vector>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

struct Coordinate {
    int x, y;
};

class Stage {
private:
    int _ID;
    Coordinate _coordinate;
    std::string _stageName;

protected:
public:
    CDC *_pDC = game_framework::CDDraw::GetBackCDC();

    // constructor
    Stage()=default;
    
    Stage(int ID, std::string name) {
        _ID = ID;
        _coordinate.x=0;
        _coordinate.y=0;
        _stageName = name;
        // _pDC = game_framework::CDDraw::GetBackCDC();
    }

    // destructor
    void deleteIt()
    {
        // game_framework::CDDraw::ReleaseBackCDC();
    }

    // setter
    void SetCoordinate(int x, int y);

    // getter
    int GetID();
    std::string GetName();
    int GetX();
    int GetY();
};