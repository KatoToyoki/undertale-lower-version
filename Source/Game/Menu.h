#pragma once
/*
#ifndef Menu
#define Menu

#include <string>
#include <vector>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

struct Coordinate {
    int x, y;
};

struct rgbColor {
    int r, g, b;
};

enum state { toOff, toOn };

// ==========================================================

class TextColor {
private:
protected:
public:
    rgbColor off, on;

    TextColor() {
        off.r = 255;
        off.g = 255;
        off.b = 255;
        on.r = 252;
        on.g = 252;
        on.b = 45;
    }
};

// ==========================================================

class Stage {
private:
    int _ID;
    Coordinate _coordinate;
    std::string _stageName;

protected:
public:
    CDC *_pDC;
    //CDC *_pDC= game_framework::CDDraw::GetBackCDC();

    // constructor
    Stage()=default;
    
    Stage(int ID, std::string name) {
        _ID = ID;
        _coordinate.x=0;
        _coordinate.y=0;
        _stageName = name;
        _pDC = game_framework::CDDraw::GetBackCDC();
    }

    // destructor
    ~Stage()
    {
        //game_framework::CDDraw::ReleaseBackCDC();
    }

    void deleteIt()
    {
        game_framework::CDDraw::ReleaseBackCDC();
    }

    // setter
    void SetCoordinate(int x, int y);

    // getter
    int GetID();
    std::string GetName();
    int GetX();
    int GetY();
};

// ==========================================================

class MenuStart:public game_framework::CTextDraw{
private:
    int currentStage;
    TextColor color;
    std::vector<Stage> stages;

    
    // to change color of text
    void ChangeColor(Stage stage, int state);
    

protected:
public:
    // constructor
    MenuStart()
    {
        currentStage = 0;
        SetUpStages();
    }

    // set up all the stages 
    void SetUpStages();
    
    // to reveal stages
    void ShowStages();
    
    // to get the key
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


#endif
*/