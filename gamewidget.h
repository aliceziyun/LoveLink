#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include "gamemodel.h"
#include "mycharacter.h"
#include "startbutton.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QMainWindow
{
    Q_OBJECT

    friend class SimpleTest;

public:
    explicit GameWidget(QWidget *parent = nullptr,bool isDoubleMode = false);
    ~GameWidget();
    bool isDouble;
    bool isPlaying = true; //判断游戏是否正在进行
    MyCharacter *p1,*p2;    //游戏角色
    StartButton *returnBtn;

    void setSingleMode();   //单人模式
    void setDoubleMode();   //双人模式
private:
    Ui::GameWidget *ui;
    QTimer *gameTimer;  // 游戏计时器
    Item *items = NULL; //游戏道具
    bool isLinking; // 维持一个连接状态的标志
    GameModel *game; // 游戏模型 
    QMediaPlayer *audioPlayer; // 音乐播放器

    void isOver();
    void initGame(); // 初始化游戏
    void addIcons(); //添加图标
    void isGetItems(); //判断是否吃到道具并实现道具效果
    void seekHint(); //得到提示
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *ev) override;

signals:
void iconEliminate(int value); //icon消除
void gameWidgetBack();  //点击返回按钮返回

public slots:
    void save();    //游戏存档
    void load();    //游戏读档
    void pause();   //游戏暂停
    void go_on();   //游戏继续
    void timeEvent();   //计时器绑定事件
    void iconSelected(); // icon点击到响应
    void iconSelected2();   //icon响应
    void on_progressbar_valueChanged(int value);
};

#endif // GAMEWIDGET_H
