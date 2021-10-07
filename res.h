#pragma once
#ifndef RES_H
#define RES_H

#include <QLabel>
#include <QObject>
#include <QString>

// ------------ 全局变量 ------------ //
// 最大行和列数
const int MAX_ROW = 15;
const int MAX_COL = 25;
const int kIconSum = 200;

// 游戏可玩图片数量
const int MAX_ICON = 9;

//图标大小
const int kIconSize = 50;

//ui界面
const int kLeftMargin = 50;
const int kTopMargin = 150;

//每关的长度
const int levelTime = 20;

//每关的目标分数
const int levelScore = 10;

// 游戏状态
enum GameStatus
{
    PLAYING,
    PAUSE,
    WIN,
    OVER
};

//游戏道具
enum GameItems
{
    TIMEPLUS,
    SHUFFLE,
    HINT,
    NONE
};

enum Muse
{
    HONOKA,
    ERI,
    KOTORI,
    UMI,
    RIN,
    MAKI,
    NOZOMI,
    HANAYO,
    NICO
};

//存档文件
extern FILE *gameSave;

// 用于绘制线段的连接点(其实应该统一用这个结构体的，代码有待优化)
struct PaintPoint
{
    PaintPoint(int _x, int _y) : x(_x), y (_y) {}
    int x;
    int y;
};

// 继承自button，存储坐标值
struct IconButton :QLabel
{
    Q_OBJECT

public:
    IconButton(QWidget *parent = Q_NULLPTR) :
        QLabel(parent),
        xID(-1),
        yID(-1),
        ID(-1)
    {
    }
    int xID; // x 坐标
    int yID; // y 坐标
    int ID; //总ID
    bool highlight = false;
    bool hintting = false;

    void setPix();
signals:
    void iconPressed();
    void iconPressed2();
};

//储存道具
struct Item: QLabel
{
public:
    Item(QWidget *parent = Q_NULLPTR) :
        QLabel(parent),
        xID(-1),
        yID(-1)
    {
    }
    int xID; // x 坐标
    int yID; // y 坐标
    GameItems gameitems;
    Item(int x,int y, GameItems i){xID = x; yID = y; gameitems = i;}

    void setPix();
};

extern IconButton *imageButton[MAX_COL*MAX_ROW]; // 图片button数组
extern IconButton *preIcon, *curIcon; // 记录点击的icon
extern IconButton *preIcon2, *curIcon2; // 记录点击的icon
#endif // RES_H
