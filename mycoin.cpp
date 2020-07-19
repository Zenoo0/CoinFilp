#include "mycoin.h"
#include<QPixmap>
#include<QMessageBox>
#include<QTimer>
mycoin::mycoin(QString CoinImg)
{
    QPixmap pix;
    bool ret = pix.load(CoinImg);
    if(!ret)
    {
        QString str = QString("图片加载失败 %1").arg(CoinImg);
       QMessageBox::critical(this,"加载失败",str);
       return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图案
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //开启定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);


    //初始化反转标志
    isAnimation = false;
    //初始化是否胜利
    isWin = false;

    //监听定时器  金币翻银币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图案
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到最后一张 停止定时器
        if(this->min > this->max)
        {
            min =1;//重置最小值
            isAnimation = false;
            timer1->stop();
        }

    });

    //监听定时器  银币翻金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图案
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到最后一张 停止定时器
        if(this->max < this->min)
        {
            this->max = 8;//重置最大值
            isAnimation = false;
            timer2->stop();
        }

    });


}

void mycoin::changeFlag()
{
    if(this->flag)//金币 翻 银币
    {
        isAnimation = true;
        timer1->start(30);
        this->flag = false;
    } else
    {
        isAnimation = true;
        timer2->start(30);
        this -> flag = true;
    }





}

void mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation|| isWin == true )
    {
        return;
    }else{
        return QPushButton::mousePressEvent(e);
    }



}
