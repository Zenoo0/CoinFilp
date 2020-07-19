#ifndef CHOOSELEVELSCENCE_H
#define CHOOSELEVELSCENCE_H
#include<QPainter>
#include <QMainWindow>
#include"mypushbutton.h"
#include"mainwindow.h"
#include<QTimer>
#include"playscene.h"
class ChooseLevelScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScence(QWidget *parent = nullptr);
    //void painterEvent(QPaintEvent*);

    PlayScene *playScene;

signals:
    //自定义信号 只需声明 不许实现
    void chooseSceneBack();


};

#endif // CHOOSELEVELSCENCE_H
