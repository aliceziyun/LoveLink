#pragma once
#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QString>
#include <QPushButton>
#include <QEvent>


class StartButton:public QPushButton
{
public:
    StartButton(QString normalImg, QString pressImg, int width, int height);
    ~StartButton(){};

private:
    int btn_height;
    int btn_width;
    QString normalPath; //普通状态路径
    QString pressPath;  //按下状态路径
    void enterEvent(QEvent *);  //重写鼠标进入事件
    void leaveEvent(QEvent *);  //重写鼠标离开事件
};

#endif // STARTBUTTON_H
