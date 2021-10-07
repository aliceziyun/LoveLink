#include "gamewidget.h"
#include "ui_gamewidget.h"

#include <QElapsedTimer>
#include <QMessageBox>
#include <QSound>
#include <QPainter>
#include <QFileDialog>
#include <QThread>

GameWidget::GameWidget(QWidget *parent,bool isDoubleMode) :
    QMainWindow(parent),
    ui(new Ui::GameWidget)
{
    //基本设置
    ui->setupUi(this);
    this->setFixedSize(1350,1000);
    this->setWindowTitle("LoveLink!");
    this->setWindowIcon(QPixmap(":/main/background/loveca.png"));
    this->show();

    //设置菜单栏
    connect(ui->actionsave1,&QAction::triggered,this,&GameWidget::save);
    connect(ui->actionload1,&QAction::triggered,this,&GameWidget::load);
    connect(ui->actionpause,&QAction::triggered,this,&GameWidget::pause);
    connect(ui->actiongoon,&QAction::triggered,this,&GameWidget::go_on);
    connect(ui->actionquit,&QAction::triggered,this,&GameWidget::close);

    connect(ui->actionreturn,&QAction::triggered,[=](){
        emit gameWidgetBack();
    });

    //初始化关卡
    preIcon = preIcon2 = curIcon = curIcon2 = NULL;
    isDouble = isDoubleMode;
    initGame();

    //设置计时器
    gameTimer = new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&GameWidget::timeEvent);
    gameTimer->start(1000);
}


GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::initGame()
{
    // 启动游戏
    game = new GameModel;
    game->startGame();
    isLinking = false;

    //设置游戏角色
    p1 = new MyCharacter;
    p1->setParent(this);
    p1->setPix(HONOKA);
    p1->setGeometry(kLeftMargin, kTopMargin, kIconSize, kIconSize);
    p1->show();
    p1->chara_x = 0;
    p1->chara_y = 0;

    p2 = new MyCharacter;
    p2->setParent(this);
    p2->setPix(KOTORI);
    p2->setGeometry(kLeftMargin + (MAX_COL -1) * kIconSize, kTopMargin + (MAX_ROW - 1) * kIconSize
                    , kIconSize, kIconSize);
    p2->chara_x = MAX_COL - 1;
    p2->chara_y = MAX_ROW - 1;
    p2->show();

    if(!isDouble)
        p2->hide();

    //设置时间标签
    QFont font;
    font.setFamily("华文新魏");
    ui->timerLabel->setFont(font);
    ui->timerLabel->setText(QString::number((game->gameTime)));

    //设置单人双人模式
    if(isDouble) setDoubleMode();
    else setSingleMode();

    items = new Item(-1,-1,NONE);

    addIcons();

    // 播放背景音乐
    audioPlayer = new QMediaPlayer(this);

    audioPlayer->setMedia(QUrl("qrc:/song/startdash.mp3"));
    audioPlayer->play();
}

void GameWidget::setSingleMode()
{
    ui->scoreLabel_2->hide();
    ui->scoreLabel_3->hide();

    //设置分数标签
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(10);
    ui->scoreLabel->setFont(font);
    ui->scoreLabel->setText(QString::number(game->score1));

    //设置进度条
    QString sll = "QProgressBar::chunk:horizontal{background:rgb(145,210,75,150);}";
    ui->progressbar->setValue(0);
    ui->progressbar->setStyleSheet(sll);
    connect(this,&GameWidget::iconEliminate,ui->progressbar,&QProgressBar::valueChanged);
}

void GameWidget::setDoubleMode()
{
    ui->progressbar->hide();
    ui->scoreLabel->hide();

    ui->scoreLabel_2->show();
    ui->scoreLabel_3->show();

    ui->scoreLabel_2->setText(QString::number(game->score1));
    ui->scoreLabel_3->setText(QString::number(game->score2));
}

void GameWidget::addIcons()
{
    // 添加button
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
    {
        imageButton[i] = new IconButton(this);
        imageButton[i]->setGeometry(kLeftMargin + (i % MAX_COL)* kIconSize, kTopMargin + (i / MAX_COL) * kIconSize, kIconSize, kIconSize);
        // 设置索引
        imageButton[i]->xID = i % MAX_COL;
        imageButton[i]->yID = i / MAX_COL;

        imageButton[i]->show();
        imageButton[i]->ID = game->gameMap[i];
        if (game->gameMap[i])
        {
            // 有方块就设置图片
            imageButton[i]->setPix();

            // 添加按下的信号槽
            connect(imageButton[i], &IconButton::iconPressed, this, &GameWidget::iconSelected);
            connect(imageButton[i], &IconButton::iconPressed2, this, &GameWidget::iconSelected2);
        }
        else
            imageButton[i]->hide();
    }
}

void GameWidget::isGetItems()
{
    if((p1->chara_x == items->xID && p1->chara_y == items->yID))
    {
        switch (items->gameitems) {
        case TIMEPLUS:
        {
            game->gameTime += 10;
            ui->timerLabel->setText(QString::number(game->gameTime));
            game->score1 += 30;
            break;
        }
        case SHUFFLE:
        {
            for(int i = 0; i < MAX_ROW * MAX_COL; i++)
                imageButton[i]->hide();
            game->shuffleGame(p1->totalNum,p2->totalNum);
            game->score1 += 40;
            addIcons();
            break;
        }
        case HINT:
        {
            seekHint();
            game->score1 += 20;
            break;
        }
        case NONE:{break;}
        }

        items->hide();
        items->gameitems = NONE;

        if(!isDouble)
        {
            iconEliminate(game->setProgress());
            ui->scoreLabel->setText(QString::number(game->score1));
        }
        else
            ui->scoreLabel_2->setText(QString::number(game->score1));
    }

    if((p2->chara_x == items->xID && p2->chara_y == items->yID))
    {
        switch (items->gameitems) {
        case TIMEPLUS:
        {
            game->gameTime += 10;
            ui->timerLabel->setText(QString::number(game->gameTime));
            game->score2 += 30;
            break;
        }
        case SHUFFLE:
        {
            for(int i = 0; i < MAX_ROW * MAX_COL; i++)
                imageButton[i]->hide();
            game->shuffleGame(p1->totalNum,p2->totalNum);
            game->score2 += 40;
            addIcons();
            break;
        }
        case HINT:
        {
            seekHint();
            game->score2 += 20;
            break;
        }
        case NONE:{break;}
        }

        items->hide();
        items->gameitems = NONE;
        ui->scoreLabel_3->setText(QString::number(game->score2));
    }
}

void GameWidget::seekHint()
{
    // 连接生成提示
    int srcX = game->hintArray[0];
    int srcY = game->hintArray[1];
    int dstX = game->hintArray[2];
    int dstY = game->hintArray[3];

    if(game->isCanLink(srcX, srcY, dstX, dstY))
    {
        //显示该方块
        IconButton *icon1 = imageButton[srcY * MAX_COL + srcX];
        IconButton *icon2 = imageButton[dstY * MAX_COL + dstX];

        icon1->highlight = true;
        icon1->setPix();
        icon1->hintting = true;

        icon2->highlight = true;
        icon2->setPix();
        icon2->hintting = true;
    }
}

void GameWidget::isOver()
{
    if(game->currentIcon == 0)
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
        emit this->gameWidgetBack();
    }
}
