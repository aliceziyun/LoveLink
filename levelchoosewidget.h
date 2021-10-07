#pragma once
#ifndef LEVELCHOOSEWIDGET_H
#define LEVELCHOOSEWIDGET_H

#include <QMainWindow>
#include "startbutton.h"
#include "gamewidget.h"

class LevelChooseWidget:public QMainWindow
{
public:
    LevelChooseWidget();
    ~LevelChooseWidget(){};

    StartButton *song1,*song2,*song3,*song4;
    GameWidget *gameWindow;

private:
    void paintEvent(QPaintEvent *) override;
};

#endif // LEVELCHOOSEWIDGET_H
