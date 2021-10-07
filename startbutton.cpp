#include "startbutton.h"

StartButton::StartButton(QString normalImg, QString pressImg, int width, int height)
{
    normalPath = normalImg;
    pressPath = pressImg;

    btn_width = width;
    btn_height = height;

    QPixmap pix;
    pix.load(normalImg);       //加载图片
    pix = pix.scaled(btn_width,btn_height);    //设置图片大小

    this->setFixedSize(btn_width,btn_height); //设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}"); //设置不规则图片样式
    this->setIcon(pix); //设置图标
    this->setIconSize(QSize(btn_width,btn_height));   //设置图标大小
}

void StartButton::enterEvent(QEvent *)
{
    QPixmap pix;
    pix.load(pressPath);       //加载图片
    pix = pix.scaled(btn_width,btn_height);    //设置图片大小

    this->setIcon(pix); //设置图标
}

void StartButton::leaveEvent(QEvent *)
{
    QPixmap pix;
    pix.load(normalPath);       //加载图片
    pix = pix.scaled(btn_width,btn_height);    //设置图片大小

    this->setIcon(pix); //设置图标
}


