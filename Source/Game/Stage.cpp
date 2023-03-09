#include "stdafx.h"
#include "Stage.h"

#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

void Stage::SetCoordinate(int x, int y) {
    _coordinate.x = x;
    _coordinate.y = y;
}

int Stage::GetID()
{
    return _ID;
}

std::string Stage::GetName()
{
    return _stageName;
}

int Stage::GetX()
{
    return _coordinate.x;
}

int Stage::GetY()
{
    return _coordinate.y;
}

