#include "helpwidget.h"

HelpWidget::HelpWidget()
{
    //基本设置
    this->setFixedSize(1350,1000);
    this->setWindowTitle("LoveLink!");
    this->setWindowIcon(QPixmap(":/main/background/loveca.png"));
    this->show();

    StartButton *returnBtn = new StartButton(":/buttons/modebutton/return.png"
                                ,":/buttons/modebutton/return_pressed.png",
                                100,60);
    returnBtn->setParent(this);
    returnBtn->move(1200,50);
    returnBtn->show();

    connect(returnBtn,&StartButton::clicked,[=](){
        emit this->helpWidgetBack();
    });

    firstPage = new QLabel;
    firstPage->setParent(this);
    QPixmap pix;
    QString fileString(":/background/background/help.png");
    pix.load(fileString);
    firstPage->setPixmap(pix);
    firstPage->setGeometry(0,0,1350,1000);

    secondPage = new QLabel;
    secondPage->setParent(this);
    QPixmap pix2;
    QString fileString2(":/background/background/help2.png");
    pix.load(fileString2);
    secondPage->setPixmap(pix2);
    secondPage->setGeometry(0,0,1350,1000);

    setFirstPage();
    returnBtn->raise();
}

void HelpWidget::setFirstPage()
{
    secondPage->hide();
    firstPage->show();
}

void HelpWidget::setSecondPage()
{
    firstPage->hide();
    secondPage->show();
}
