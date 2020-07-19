#include "chooselevelscence.h"
#include<QMenuBar>
#include<QLabel>
ChooseLevelScence::ChooseLevelScence(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置标题图案
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置菜单栏
    QMenuBar *bar = new QMenuBar(this);
    this->setMenuBar(bar);
    //设置菜单项
    QMenu *menu = bar->addMenu("开始");
    QAction*quiteAction = menu->addAction("退出");
    //点击退出按钮  实现退出功能
    connect(quiteAction,&QAction::triggered,[=](){
        //退出
        this->close();

    });

    //通过label设置背景图片
    QLabel *label = new QLabel;
    label->setParent(this);
    label->setFixedSize(this->width(),this->height()+30);
    //label->setScaledContents(true);
    QPixmap pix(":/res/OtherSceneBg.png");
    label->setPixmap(pix);
    label->show();

    //通过label设置标题图案
    QLabel *label2 = new QLabel;
    label2->setParent(label);
    QPixmap pix2(":/res/Title.png");
    label2->setPixmap(pix2);
    label2->move((this->width() - pix2.width())*0.5,30);
    label2->show();


    //设置返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(label);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

   //返回主场景
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"lalaal";
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();
        });
    });

    playScene = nullptr;

    //关卡按钮
    for(int i = 0 ;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(label);
        menuBtn->move(25+(i%4)*70,150+(i/4)*70);

        connect(menuBtn,&MyPushButton::clicked,[=](){

            menuBtn->zoom(true);
            menuBtn->zoom(false);
            QTimer::singleShot(500,label,[=](){
//                QString str = QString("您选择的是第 %1 关").arg(i+1);
//                qDebug()<<str;
                //切换到具体游戏场景
                this->hide();//隐藏自身
                playScene = new PlayScene(i+1);
                playScene->show();

                //从第三场景返回到该场景
                connect(playScene,&PlayScene::backchoosescence,[=](){
                    this->show();
                });

            });
        });

        //关卡数字
        QLabel *mlabel = new QLabel(label);
        mlabel->setFixedSize(menuBtn->width(),menuBtn->height());
        mlabel->move(25+(i%4)*70,150+(i/4)*70);
        mlabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        mlabel->setText(QString::number(i+1));
        mlabel->setAttribute(Qt::WA_TransparentForMouseEvents);//51号  鼠标穿透事件


    }




}

//void ChooseLevelScence::painterEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//      QPixmap pix;
//      pix.load(":/res/OtherSceneBg.png");
//      painter.drawPixmap(0,0,this->width(),this->height(),pix);
//       //加载标题
//      pix.load(":/res/Title.png");
//      painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
//}


