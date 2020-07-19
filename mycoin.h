#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit mycoin(QWidget *parent = nullptr);

    //显示默认的是金币还是银币
    mycoin(QString CoinImg);

    int posX;//x坐标
    int posY;//y坐标
    bool flag;//正反标志

    void changeFlag();//改变标志  执行 反转效果
    QTimer *timer1; //正面翻反面 定时器
    QTimer *timer2; //反面翻正面 定时器
    int min = 1;//最小图片
    int max = 8;//最大图片

    bool isAnimation;//做反转动画的标志   优化金币反转效果

    bool isWin;

    //鼠标点击事件
    void mousePressEvent(QMouseEvent *);

signals:

};

#endif // MYCOIN_H
