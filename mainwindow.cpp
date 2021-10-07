#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QElapsedTimer>
#include <QMessageBox>
#include <QSound>
#include <QPainter>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1350,1000);
    this->setWindowTitle("LoveLink!");
    this->setWindowIcon(QPixmap(":/main/background/loveca.png"));
    this->show();

    connect(ui->actionnew,&QAction::triggered,this,&MainWindow::newGame);
    connect(ui->actionquit,&QAction::triggered,this,&MainWindow::close);

    // 创建开始按钮对象
    StartButton *startbtn = new StartButton(":/main/background/mainbutton.png"
                                            ,":/main/background/mainbutton_select.png"
                                            ,250,140);
    startbtn->setParent(this);
    startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5,this->height() * 0.74);
    startbtn->show();
    connect(startbtn,&StartButton::clicked,this,&MainWindow::newGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    this->hide();
    modeWidget = new ModeChooseWidget;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/main/background/mainttitle.jpg");
    pix = pix.scaled(1350,800);
    painter.drawPixmap(0,100,1350,800,pix);
}
