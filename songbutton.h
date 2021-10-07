#ifndef SONGBUTTON_H
#define SONGBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QEvent>

class SongButton:public QPushButton
{
public:
    SongButton();
    ~SongButton(){};
    bool unlock = false;    //判断歌曲是否解锁

private:
    int btn_height;
    int btn_width;
    int songNumber; //歌曲编号
    QString normalPath;
    QString pressPath;
    QString lockPath;
    void enterEvent(QEvent *);  //重写鼠标进入事件
    void leaveEvent(QEvent *);
};

#endif // SONGBUTTON_H
