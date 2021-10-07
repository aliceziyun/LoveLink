#pragma once
#ifndef MYCHARACTER_H
#define MYCHARACTER_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include "gamemodel.h"

class MyCharacter:public QLabel
{
public:
    MyCharacter(){};
    ~MyCharacter(){};
    int chara_x = 0;
    int chara_y = 0;
    int player = 1;
    int totalNum = chara_x * MAX_ROW + chara_y;

    void setPix(Muse chara);
};

#endif // MYCHARACTER_H
