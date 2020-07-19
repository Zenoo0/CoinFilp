#include "mypushbutton.h"


MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->pressImgpath = pressImg;
    this->normalImgpath = normalImg;
    QPixmap pix;
    bool ret = pix.load(this->normalImgpath);
    if(!ret)
    {
        QString str = QString("%1 图片加载失败").arg(this->pressImgpath);
        qDebug()<<str;
        return;
    }
    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置图片不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图片
    this->setIcon(pix);
    //设置按钮图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));



}

void MyPushButton::zoom(bool t)
{
    if(t)
    {
        //设置向下弹效果
        QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
        //设置时长 单位 毫秒
        animation->setDuration(200);
        //设置开始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //设置结束位置
        animation->setEndValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));
        //设置动画曲线
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始
        animation->start();

    }else{
        //设置向上弹效果
        QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
        //设置时长 单位 毫秒
        animation->setDuration(200);
        //设置开始位置
        animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
        //设置结束位置
        animation->setEndValue(QRect(this->x(),this->y() ,this->width(),this->height()));
        //设置动画曲线
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始
        animation->start();
    }

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgpath!="")//如果选中的路径不为空，显示选中图片
    {
        QPixmap pix;
        bool ret = pix.load(pressImgpath);
        if(!ret)
        {
            qDebug()<<pressImgpath<<"图片加载失败";
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置图片不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图片
        this->setIcon(pix);
        //设置按钮图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(pressImgpath!="")
    {
        QPixmap pix;
        bool ret = pix.load(pressImgpath);
        if(!ret)
        {
            qDebug()<<pressImgpath<<"图片加载失败";
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置图片不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图片
        this->setIcon(pix);
        //设置按钮图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    return QPushButton::mouseReleaseEvent(e);

}


