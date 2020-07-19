#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QWidget>
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QFont>
#include"mycoin.h"
#include"mypushbutton.h"
#include"dataconfig.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);

    //记录当前关卡号
    int levelIndex;

    //游戏二维数组 维护里面金币和银币标志
    int gameArray[4][4];

    mycoin * coinBtn[4][4]; //金币按钮数组

    bool isWin ;//判断是否胜利


signals:
    void backchoosescence();
};

#endif // PLAYSCENE_H
