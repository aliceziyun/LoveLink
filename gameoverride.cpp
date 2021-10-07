#include "gamewidget.h"

#include <QPainter>

void GameWidget::keyPressEvent(QKeyEvent *ev) //之后优化，写成switch，稍微好看一点
{
    //p1
    if(ev->key() == Qt::Key_Up && p1->chara_y >= 0)
    {
        qDebug()<<game->gameMap[p1->chara_x + (p1->chara_y - 1) * MAX_COL];
        if(p1->chara_y - 1 == -1 || p1->chara_x == -1 || p1->chara_x == MAX_COL ||
                !game->gameMap[p1->chara_x + (p1->chara_y - 1) * MAX_COL])
        {
            p1->chara_y -= 1;
            p1->move(kLeftMargin + p1->chara_x * kIconSize, kTopMargin + p1->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p1->totalNum - MAX_COL])
                imageButton[p1->totalNum - MAX_COL]->iconPressed();
    }
    if(ev->key() == Qt::Key_Down && p1->chara_y < MAX_ROW)
    {
        if(p1->chara_y + 1 == MAX_ROW || p1->chara_x == -1 || p1->chara_x == MAX_COL ||
                !game->gameMap[p1->chara_x + (p1->chara_y + 1) * MAX_COL])
        {
            p1->chara_y += 1;
            p1->move(kLeftMargin + p1->chara_x * kIconSize, kTopMargin + p1->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p1->totalNum + MAX_COL])
                imageButton[p1->totalNum + MAX_COL]->iconPressed();

    }
    if(ev->key() == Qt::Key_Left && p1->chara_x >= 0)
    {
        if(p1->chara_x -1 == -1 || p1->chara_y == -1|| p1->chara_y == MAX_ROW ||
                !game->gameMap[p1->chara_x + p1->chara_y * MAX_COL - 1])
        {
            p1->chara_x -= 1;
            p1->move(kLeftMargin + p1->chara_x * kIconSize, kTopMargin + p1->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p1->totalNum - 1])
                imageButton[p1->totalNum - 1]->iconPressed();
    }
    if(ev->key() == Qt::Key_Right && p1->chara_x < MAX_COL)
    {
        if(p1->chara_x + 1 == MAX_COL || p1->chara_y == -1|| p1->chara_y == MAX_ROW ||
                !game->gameMap[p1->chara_x + p1->chara_y * MAX_COL + 1])
        {
            p1->chara_x +=1;
            p1->move(kLeftMargin + p1->chara_x * kIconSize, kTopMargin + p1->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p1->totalNum + 1])
                imageButton[p1->totalNum + 1]->iconPressed();
    }

    //p2
    if(ev->key() == Qt::Key_W && p2->chara_y >= 0)
    {
        if(p2->chara_y - 1 == -1 || p2->chara_x == -1 || p2->chara_x == MAX_COL ||
                !game->gameMap[p2->chara_x + (p2->chara_y - 1) * MAX_COL])
        {
            p2->chara_y -= 1;
            p2->move(kLeftMargin + p2->chara_x * kIconSize, kTopMargin + p2->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p2->totalNum - MAX_COL])
                imageButton[p2->totalNum - MAX_COL]->iconPressed2();

    }
    if(ev->key() == Qt::Key_S && p2->chara_y < MAX_ROW)
    {
        if(p2->chara_y + 1 == MAX_ROW || p2->chara_x == -1 || p2->chara_x == MAX_COL ||
                !game->gameMap[p2->chara_x + (p2->chara_y + 1) * MAX_COL])
        {
            p2->chara_y += 1;
            p2->move(kLeftMargin + p2->chara_x * kIconSize, kTopMargin + p2->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p2->totalNum + MAX_COL])
                imageButton[p2->totalNum + MAX_COL]->iconPressed2();

    }
    if(ev->key() == Qt::Key_A && p2->chara_x >= 0)
    {
        if(p2->chara_x -1 == -1 || p2->chara_y == -1|| p2->chara_y == MAX_ROW ||
                !game->gameMap[p2->chara_x + p2->chara_y * MAX_COL - 1])
        {
            p2->chara_x -= 1;
            p2->move(kLeftMargin + p2->chara_x * kIconSize, kTopMargin + p2->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p2->totalNum -1])
                imageButton[p2->totalNum -1]->iconPressed2();

    }
    if(ev->key() == Qt::Key_D && p2->chara_x < MAX_COL)
    {
        if(p2->chara_x + 1 == MAX_COL || p2->chara_y == -1|| p2->chara_y == MAX_ROW ||
                !game->gameMap[p2->chara_x + p2->chara_y * MAX_COL + 1])
        {
            p2->chara_x +=1;
            p2->move(kLeftMargin + p2->chara_x * kIconSize, kTopMargin + p2->chara_y * kIconSize);
        }
        else
            if(game->gameMap[p2->totalNum +1])
                imageButton[p2->totalNum +1]->iconPressed2();
    }

    p1->totalNum = p1->chara_x + p1->chara_y * MAX_COL;
    p2->totalNum = p2->chara_x + p2->chara_y * MAX_COL;

    isGetItems();
}

void GameWidget::paintEvent(QPaintEvent* )
{
    if(!isPlaying) return;
    //绘制背景图
    QPainter painter(this);
    QPixmap pix,pix2,pix3,pix4,pix5,pix6;

    pix.load(":/background/background/sky.png");
    pix = pix.scaled(QSize(1350,1000));
    painter.drawPixmap(0,0,1350,1000,pix);

    pix2.load(":/background/background/school.png");
    pix2 = pix2.scaled(QSize(1200,600));
    painter.drawPixmap(50,150,1250,750,pix2);

    pix4.load(":/background/background/time.png");
    pix4 = pix4.scaled(QSize(180,72));
    painter.drawPixmap(1100,55,180,72,pix4);

    if(!isDouble)
    {
        pix3.load(":/background/background/score.png");
        pix3 = pix3.scaled(QSize(280,40));
        painter.drawPixmap(780,73,280,40,pix3);
    }
    else
    {
        pix5.load(":/background/background/p1.png");
        pix5 = pix5.scaled(QSize(250,60));
        painter.drawPixmap(100,65,250,60,pix5);

        pix6.load(":/background/background/p2.png");
        pix6 = pix6.scaled(QSize(500,60));
        painter.drawPixmap(500,65,250,60,pix6);
    }

    // 重绘时会调用，可以手动调用
    QPen pen;
    QColor color(rand() % 256, rand() % 256, rand() % 256);
    pen.setColor(color);
    pen.setWidth(5);
    painter.setPen(pen);

    // 连接各点画线
    for (int i = 0; i < int(game->paintPoints.size()) - 1; i++)
    {
        PaintPoint p1 = game->paintPoints[i];
        PaintPoint p2 = game->paintPoints[i + 1];

        // 拿到各button的坐标,注意边缘点坐标
        QPoint btn_pos1;
        QPoint btn_pos2;

        // p1
        if (p1.x == -1)
        {
            btn_pos1 = imageButton[p1.y * MAX_COL + 0]->pos();
            btn_pos1 = QPoint(btn_pos1.x() - kIconSize, btn_pos1.y());
        }
        else if (p1.x == MAX_COL)
        {
            btn_pos1 = imageButton[p1.y * MAX_COL + MAX_COL - 1]->pos();
            btn_pos1 = QPoint(btn_pos1.x() + kIconSize, btn_pos1.y());
        }
        else if (p1.y == -1)
        {
            btn_pos1 = imageButton[0 + p1.x]->pos();
            btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() - kIconSize);
        }
        else if (p1.y == MAX_ROW)
        {
            btn_pos1 = imageButton[(MAX_ROW - 1) * MAX_COL + p1.x]->pos();
            btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() + kIconSize);
        }
        else
            btn_pos1 = imageButton[p1.y * MAX_COL + p1.x]->pos();

        // p2
        if (p2.x == -1)
        {
            btn_pos2 = imageButton[p2.y * MAX_COL + 0]->pos();
            btn_pos2 = QPoint(btn_pos2.x() - kIconSize, btn_pos2.y());
        }
        else if (p2.x == MAX_COL)
        {
            btn_pos2 = imageButton[p2.y * MAX_COL + MAX_COL - 1]->pos();
            btn_pos2 = QPoint(btn_pos2.x() + kIconSize, btn_pos2.y());
        }
        else if (p2.y == -1)
        {
            btn_pos2 = imageButton[0 + p2.x]->pos();
            btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() - kIconSize);
        }
        else if (p2.y == MAX_ROW)
        {
            btn_pos2 = imageButton[(MAX_ROW - 1) * MAX_COL + p2.x]->pos();
            btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() + kIconSize);
        }
        else
            btn_pos2 = imageButton[p2.y * MAX_COL + p2.x]->pos();

        // 中心点
        QPoint pos1(btn_pos1.x() + kIconSize / 2, btn_pos1.y() + kIconSize / 2);
        QPoint pos2(btn_pos2.x() + kIconSize / 2, btn_pos2.y() + kIconSize / 2);

        painter.drawLine(pos1, pos2);
    }
    game->paintPoints.clear();
}
