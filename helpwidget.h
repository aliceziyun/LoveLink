#pragma once
#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QMainWindow>
#include "startbutton.h"
#include <QLabel>

class HelpWidget:public QMainWindow
{
    Q_OBJECT
public:
    HelpWidget();

    QLabel *firstPage,*secondPage;

signals:
    void helpWidgetBack();

public slots:
    void setFirstPage();
    void setSecondPage();
};

#endif // HELPWIDGET_H
