#include "gamewidget.h"
#include "ui_gamewidget.h"

#include <QMainWindow>
#include <QWidget>
#include <QSound>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QElapsedTimer>
#include <QMessageBox>

void GameWidget::save()
{
    //打开存档文件
    if((gameSave = fopen("save1.txt","w+")) == NULL)
        return;

    //保存游戏模式
    fwrite(&isDouble,sizeof(isDouble),1,gameSave);
    //保存游戏地图
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
        fwrite(&(game->gameMap[i]),sizeof(game->gameMap),1,gameSave);
    //保存人物坐标
    fwrite(&(p1->chara_x),sizeof(p1->chara_x),1,gameSave);
    fwrite(&(p1->chara_y),sizeof(p1->chara_y),1,gameSave);
    //保存当前游戏时间
    fwrite(&(game->gameTime),sizeof(game->gameTime),1,gameSave);
    //保存方块数
    fwrite(&(game->currentIcon),sizeof(game->currentIcon),1,gameSave);
    //保存分数
    fwrite(&(game->score1),sizeof(game->score1),1,gameSave);
    //保存当前道具
    fwrite(&(items->xID),sizeof(items->xID),1,gameSave);
    fwrite(&(items->yID),sizeof(items->yID),1,gameSave);
    fwrite(&(items->gameitems),sizeof(items->gameitems),1,gameSave);

    if(isDouble)
    {
        fwrite(&(p2->chara_x),sizeof(p2->chara_x),1,gameSave);
        fwrite(&(p2->chara_y),sizeof(p2->chara_y),1,gameSave);
        fwrite(&(game->score2),sizeof(game->score2),1,gameSave);
    }

    fclose(gameSave);
}

void GameWidget::load()
{ 
    //读取游戏地图
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
        imageButton[i]->hide();
    items->hide();

    //读取游戏存档
    gameSave = fopen("save1.txt","r");

    //保存游戏模式
    fread(&isDouble,sizeof(isDouble),1,gameSave);
    //读取游戏地图
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
        fread(&(game->gameMap[i]),sizeof(game->gameMap),1,gameSave);
    //读取人物坐标
    fread(&(p1->chara_x),sizeof(p1->chara_x),1,gameSave);
    fread(&(p1->chara_y),sizeof(p1->chara_y),1,gameSave);
    //读取当前游戏时间
    fread(&(game->gameTime),sizeof(game->gameTime),1,gameSave);
    //读取方块数
    fread(&(game->currentIcon),sizeof(game->currentIcon),1,gameSave);
    fread(&(game->score1),sizeof(game->score1),1,gameSave);
    //读取当前道具
    fread(&(items->xID),sizeof(items->xID),1,gameSave);
    fread(&(items->yID),sizeof(items->yID),1,gameSave);
    fread(&(items->gameitems),sizeof(items->gameitems),1,gameSave);

    if(isDouble)
    {
        fread(&(p2->chara_x),sizeof(p2->chara_x),1,gameSave);
        fread(&(p2->chara_y),sizeof(p2->chara_y),1,gameSave);
        fread(&(game->score2),sizeof(game->score2),1,gameSave);
    }

    addIcons();
    p1->move(kLeftMargin + p1->chara_x * kIconSize, kTopMargin + p1->chara_y * kIconSize);
    ui->timerLabel->setText(QString::number(game->gameTime));
    ui->progressbar->setValue(game->setProgress());
    items->setPix();
    items->move(kLeftMargin + items->xID * kIconSize, kTopMargin + items->yID * kIconSize);
    items->show();

    fclose(gameSave);
}

void GameWidget::pause()
{
    isPlaying = false;
    gameTimer->stop();
}

void GameWidget::go_on()
{
    isPlaying = true;
    gameTimer->start(1000);
}

void GameWidget::timeEvent()
{
    if(!isPlaying)
        return;
    if(game->gameTime == 0)
    {
        gameTimer->stop();
        if(!isDouble)
        {
            if(game->isWin())
            {
                QSound::play(":/sound/win.wav");
                QMessageBox::information(this, "演唱会成功", "好耶！！！");
            }
            else
            {
                QSound::play(":/sound/lose.wav");
                QMessageBox::information(this, "演唱会失败", "再接再厉");
            }
        }
        else
        {
            if(game->score1 > game->score2)
                QMessageBox::information(this, "结果","1号偶像胜出");
            if(game->score1 < game->score2)
                QMessageBox::information(this, "结果","2号偶像胜出");
            if(game->score1 == game->score2)
                QMessageBox::information(this, "结果","平手");
        }
        gameTimer->stop();
        emit this->gameWidgetBack();
    }
    ui->timerLabel->setText(QString::number(--(game->gameTime)));

    if(game->gameTime != levelTime && (game->gameTime % 10 == 0))
    {
        items->hide();
        delete items;
        srand((unsigned)time(0));
        int randomAxis = rand() % (MAX_COL * MAX_ROW);

        while(game->gameMap[randomAxis])
            randomAxis = rand() % (MAX_COL * MAX_ROW);
        int x = randomAxis % MAX_COL;
        int y = randomAxis / MAX_COL;

        int randomID = rand() % 3;
        switch (randomID){
        case TIMEPLUS:{
            items = new Item(x,y,TIMEPLUS);
            break;
        }
        case SHUFFLE:{
            items = new Item(x,y,SHUFFLE);
            items->setParent(this);
            items->show();
            break;
        }
        case HINT:{
            items = new Item(x,y,HINT);
            items->setParent(this);
            items->show();
            game->isHint = true;
            break;
        }
        case NONE:{break;}
        }
        items->setPix();
        items->setParent(this);
        items->setGeometry(kLeftMargin + items->xID * kIconSize, kTopMargin + (items->yID) * kIconSize, kIconSize, kIconSize);
        items->show();
    }

    if(game->gameTime != levelTime && ((game->gameTime - 1) % 10 == 0))
        game->isHint = false;
}

void GameWidget::iconSelected()
{
    if (isLinking)
    {
        return;
    }

    //创建一个延时计时器
    QElapsedTimer timer;

    QSound::play(":/sound/click.wav");

    // 记录当前点击的icon
    curIcon = dynamic_cast<IconButton *>(sender());
    //如果是同一个Icon
    if(!preIcon)
    {
        curIcon->highlight = true;
        curIcon->setPix();
        preIcon = curIcon;
    }
    else
    {
        if(curIcon != preIcon)
        {
            // 如果不是同一个Icon就都标记,尝试连接
            // 锁住当前状态
            isLinking = true;

            curIcon->highlight = true;
            curIcon->setPix();
            if(game->linkTwoTiles(preIcon->xID, preIcon->yID, curIcon->xID, curIcon->yID))
            {
                update();

                timer.start();
                while(timer.elapsed() < 200)             //等待时间流逝0.2秒钟
                    QCoreApplication::processEvents();   //处理事件

                //如果两个对象均为提示方块
                if(curIcon->hintting && preIcon->hintting)
                    if(game->isHint)
                    {
                        if(!isDouble)
                        {
                            iconEliminate(game->setProgress());
                            game->score1 += 50;
                        }
                        game->isFrozen();
                        seekHint();
                    }

                // 延迟后实现连接效果
                timer.start();
                while(timer.elapsed() < 300)             //等待时间流逝0.3秒钟
                    QCoreApplication::processEvents();   //处理事件
                QSound::play(":/sound/eliminate.wav");
                curIcon->hide();
                preIcon->hide();

                preIcon = NULL;
                curIcon = NULL;

                //得分增加

                game->score1 = game->score1 + 10;
                if(!isDouble)
                {
                    iconEliminate(game->setProgress());
                    ui->scoreLabel->setText(QString::number(game->score1));
                }
                else ui->scoreLabel_2->setText(QString::number(game->score1));

                //Icon数量减少
                game->currentIcon = game->currentIcon - 2;

                // 每次检查一下是否僵局
                if (game->isFrozen())
                {
                    gameTimer->stop();
                    QMessageBox::information(this, "演唱会失败", "再接再厉");
                    emit this->gameWidgetBack();
                }

                // 检查是否胜利
                isOver();
            }
            else
            {
                // 消除失败，恢复
                timer.start();
                while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟
                    QCoreApplication::processEvents();   //处理事件
                curIcon->highlight = false;
                preIcon->highlight = false;
                curIcon->setPix();
                preIcon->setPix();

                // 指针置空，用于下次点击判断
                preIcon = NULL;
                curIcon = NULL;
            }
        }
        isLinking = false;
        update();
    }
}

void GameWidget::iconSelected2()
{
    if (isLinking)
    {
        return;
    }

    //创建一个延时计时器
    QElapsedTimer timer;

    QSound::play(":/sound/click.wav");

    // 记录当前点击的icon
    curIcon2 = dynamic_cast<IconButton *>(sender());
    //如果是同一个Icon
    if(!preIcon2)
    {
        curIcon2->highlight = true;
        curIcon2->setPix();
        preIcon2 = curIcon2;
    }
    else
    {
        if(curIcon2 != preIcon2)
        {
            // 如果不是同一个Icon就都标记,尝试连接
            // 锁住当前状态
            isLinking = true;

            curIcon2->highlight = true;
            curIcon2->setPix();
            if(game->linkTwoTiles(preIcon2->xID, preIcon2->yID, curIcon2->xID, curIcon2->yID))
            {
                update();
                qDebug()<<curIcon2->hintting<<preIcon2->hintting;

                timer.start();
                while(timer.elapsed() < 200)             //等待时间流逝0.2秒钟
                    QCoreApplication::processEvents();   //处理事件

                //如果两个对象均为提示方块
                if(curIcon2->hintting && preIcon2->hintting)
                    if(game->isHint)
                    {
                        if(!isDouble)
                        {
                            iconEliminate(game->setProgress());
                            game->score1 += 50;
                        }
                        game->isFrozen();
                        seekHint();
                    }

                // 延迟后实现连接效果
                timer.start();
                while(timer.elapsed() < 300)             //等待时间流逝0.3秒钟
                    QCoreApplication::processEvents();   //处理事件
                QSound::play(":/sound/eliminate.wav");
                curIcon2->hide();
                preIcon2->hide();

                preIcon2 = NULL;
                curIcon2 = NULL;

                //得分增加
                game->score2 = game->score2 + 10;
                ui->scoreLabel_3->setText(QString::number(game->score2));

                //Icon数量减少
                game->currentIcon = game->currentIcon - 2;

                // 每次检查一下是否僵局
                if (game->isFrozen())
                {
                    gameTimer->stop();
                    QMessageBox::information(this, "演唱会失败", "再接再厉");
                    emit this->gameWidgetBack();
                }

                // 检查是否胜利
                isOver();
            }
            else
            {
                // 消除失败，恢复
                timer.start();
                while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟
                    QCoreApplication::processEvents();   //处理事件
                curIcon2->highlight = false;
                preIcon2->highlight = false;
                curIcon2->setPix();
                preIcon2->setPix();

                // 指针置空，用于下次点击判断
                preIcon2 = NULL;
                curIcon2 = NULL;
            }
        }
        isLinking = false;
        update();
    }
}


void GameWidget::on_progressbar_valueChanged(int value)
{
    ui->progressbar->setValue(value);
}

