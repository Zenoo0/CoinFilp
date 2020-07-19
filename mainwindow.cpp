#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置退出按键
    connect(ui->actionquite,&QAction::triggered,[=](){
        this->close();
    });

    //设置标题
    this->setWindowTitle("翻金币");
    //设置标图案
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置背景图案
    this->setFixedSize(320,588);

    //设置开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //设置第二卡场景  关卡选择
    ChooseLevelScence *chooseScence = new ChooseLevelScence;

    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"牛逼！";
        //点击开始按钮 执行弹跳效果
        startBtn->zoom(true);//向下弹
        startBtn->zoom(false);//向上弹
        //延时进入第二个场景
        QTimer::singleShot(500,this,[=](){
            //隐藏主场景
            this->hide();
            //显示第二个场景
            chooseScence->show();
        });
    });

    //从第二卡场景切换为第一个场景
    connect(chooseScence,&ChooseLevelScence::chooseSceneBack,[=](){

        chooseScence->hide();
        this->show();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //设置主场景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题图片
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//设置标题图片大小为原来的0.5倍
    painter.drawPixmap(10,30,pix);

}

