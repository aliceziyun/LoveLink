#include "songbutton.h"

SongButton::SongButton()
{

}

void SongButton::enterEvent(QEvent *)
{
    QPixmap pix;
    pix.load(pressPath);       //加载图片
    pix = pix.scaled(btn_width,btn_height);    //设置图片大小

    this->setIcon(pix); //设置图标
}

void SongButton::leaveEvent(QEvent *)
{
    QPixmap pix;
    pix.load(normalPath);       //加载图片
    pix = pix.scaled(btn_width,btn_height);    //设置图片大小

    this->setIcon(pix); //设置图标
}
