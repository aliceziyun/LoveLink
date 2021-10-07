#include "levelchoosewidget.h"
#include <QPainter>

LevelChooseWidget::LevelChooseWidget()
{
    this->setFixedSize(1350,1000);
    this->setWindowTitle("LoveLink!");
    this->setWindowIcon(QPixmap(":/main/background/loveca.png"));
    this->show();

    song1 = new StartButton(":/song/song/startdash_3.jpg",":/song_select/song/startdash_3_select.jpg",
                            150,150);
    song1->setParent(this);
    song1->move(250,220);
    song1->show();
    connect(song1,&QPushButton::clicked,[=](){
        this->hide();
        gameWindow = new GameWidget;
    });
}

void LevelChooseWidget::paintEvent(QPaintEvent *)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/background/muse_song.png");
    painter.drawPixmap(0,100,1350,800,pix);
}
