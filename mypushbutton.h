#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QDebug>
#include <QPushButton>
#include<QPropertyAnimation>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg ="");
    QString normalImgpath;
    QString pressImgpath;

    //上下下弹
    void zoom(bool t);

    //鼠标事件
    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);


signals:

};

#endif // MYPUSHBUTTON_H
