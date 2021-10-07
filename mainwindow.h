#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "startbutton.h"
#include "modechoosewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ModeChooseWidget *modeWidget ;

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *) override;

public slots:
    void newGame();

};

#endif // MAINWINDOW_H
