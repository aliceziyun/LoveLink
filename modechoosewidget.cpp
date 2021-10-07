#include "modechoosewidget.h"
#include <QPainter>
#include <QMessageBox>

ModeChooseWidget::ModeChooseWidget(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(1350,1000);
    this->setWindowTitle("LoveLink!");
    this->setWindowIcon(QPixmap(":/main/background/loveca.png"));
    this->show();

    //创建按钮对象并实例化
    single_btn = new StartButton(":/buttons/modebutton/single.png"
                                 ,":/buttons/modebutton/single_pressed.png"
                                 ,500,90);
    single_btn->setParent(this);
    single_btn->move(700,150);
    single_btn->show();
    connect(single_btn,&QPushButton::clicked,[=](){
        this->hide();
        gamewidget = new GameWidget(parent,false);
        gamewidget->show();
        gamewidget->setAttribute(Qt::WA_DeleteOnClose);

        connect(gamewidget,&GameWidget::gameWidgetBack,[=](){
            gamewidget->close();
            this->show();
        });
    });


    double_btn = new StartButton(":/buttons/modebutton/double.png"
                                 ,":/buttons/modebutton/double_pressed.png"
                                 ,500,91);
    double_btn->setParent(this);
    double_btn->move(700,300);
    double_btn->show();
    connect(double_btn,&QPushButton::clicked,[=](){
        this->hide();
        gamewidget = new GameWidget(parent,true);
        gamewidget->show();
        gamewidget->setAttribute(Qt::WA_DeleteOnClose);

        connect(gamewidget,&GameWidget::gameWidgetBack,[=](){
            gamewidget->close();
            this->show();
        });
    });

    song_btn = new StartButton(":/buttons/modebutton/song.png"
                               ,":/buttons/modebutton/song_pressed.png"
                               ,505,95);
    song_btn->setParent(this);
    song_btn->move(700,450);
    song_btn->show();
    connect(song_btn,&QPushButton::clicked,[=](){
        if(gameSave == NULL)
            QMessageBox::information(this, "失败", "没有可用存档");
        else
        {
            this->hide();
            gamewidget = new GameWidget(parent,false);
            gamewidget->load();
            gamewidget->show();
        }
    });


    help_btn = new StartButton(":/buttons/modebutton/help.png"
                               ,":/buttons/modebutton/help_pressed.png"
                               ,502,94);
    help_btn->setParent(this);
    help_btn->move(700,600);
    help_btn->show();
    connect(help_btn,&QPushButton::clicked,[=](){
        this->hide();
        helpwidget = new HelpWidget();
        helpwidget->show();
        helpwidget->setAttribute(Qt::WA_DeleteOnClose);

        connect(helpwidget,&HelpWidget::helpWidgetBack,[=](){
            helpwidget->close();
            this->show();
        });
    });

    other_btn = new StartButton(":/buttons/modebutton/other.png"
                                ,":/buttons/modebutton/other_pressed.png"
                                ,500,93);
    other_btn->setParent(this);
    other_btn->move(700,750);
    other_btn->show();
}

ModeChooseWidget::~ModeChooseWidget()
{

}

void ModeChooseWidget::paintEvent(QPaintEvent *)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/background/muse.png");
    pix = pix.scaled(1350,800);
    painter.drawPixmap(0,100,1350,800,pix);

    //绘制九人图
    pix.load(":/main/background/ninegirls.jpg");
    pix = pix.scaled(598,800);
    painter.drawPixmap(50,100,598,800,pix);
}
