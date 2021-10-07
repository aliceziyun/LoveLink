#pragma once
#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QWidget>
#include "res.h"

class GameModel
{
public:
    GameModel(){};
    virtual ~GameModel(){};
    void startGame(); // 开始游戏
    void startTest();

    //游戏地图
    int *gameMap;

    GameStatus checkGameStatus(); // 判断获得游戏状态，是否输赢
    int score1 = 0 ,score2 = 0;  //分数
    int currentIcon; //当前方块数
    bool isHint = false; //判断是否处于提示状态
    int gameTime = levelTime;
    bool linkTwoTiles(int srcX, int srcY, int dstX,int dstY); // 连接起点和终点方块，连接是否成功
    bool isCanLink(int srcX, int srcY, int dstX, int dstY); // 判断起点到终点的方块是否可以连接消除
    bool isFrozen(); // 判断是否已经成为了僵局
    bool isWin(); // 检查游戏是否胜利
    int *hintArray; // 游戏提示，存储2个点
    int setProgress(){return score1;}
    void shuffleGame(int currentpos1,int currentpos2); //打乱方块
    void testLoad(); //测试读档
    std::vector<PaintPoint> paintPoints; // 用于绘制的点

    // 游戏状态和难度
    GameStatus gameStatus;
private:
    bool canLinkDirectly(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithOneCorner(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithTwoCorner(int srcX, int srcY, int dstX, int dstY);

    // 提示模式还是连接模式判断
    bool isFrozenMode;
};

#endif // GAMEMODEL_H
