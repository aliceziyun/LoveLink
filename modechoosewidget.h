#pragma once
#ifndef MODECHOOSEWIDGET_H
#define MODECHOOSEWIDGET_H

#include <QMainWindow>
#include "startbutton.h"
#include "gamewidget.h"
#include "helpwidget.h"

class ModeChooseWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModeChooseWidget(QWidget *parent = nullptr);
    ~ModeChooseWidget();

    StartButton *single_btn, *double_btn, *help_btn, *other_btn, *song_btn;
    GameWidget *gamewidget;
    HelpWidget *helpwidget;


private:
    void paintEvent(QPaintEvent *) override;
};

#endif // MODECHOOSEWIDGET_H
