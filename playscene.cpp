#include "playscene.h"



PlayScene::PlayScene(int index)
{
//    QString str = QString("打开了第 %1 关").arg(index);
//    qDebug()<<str;
    levelIndex = index;

    //设置窗口大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币场景");
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

    //通过标签绘制背景图案
    QLabel *labelBj =  new QLabel(this);
    labelBj->setFixedSize(this->width(),this->height()+30);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    labelBj->setPixmap(pix);
    labelBj->show();
    //通过标签绘制标题图案
    QLabel*labelBt = new QLabel(labelBj);
    pix.load(":/res/Title.png");
   // labelBt->setFixedSize(pix.width()*0.5,pix.height()*0.5);
    labelBt->resize(pix.width()*0.5,pix.height()*0.5);
    labelBt->setScaledContents(true);//自适应大小
    labelBt->move((this->width() - pix.width())*0.5,30);
    labelBt->setPixmap(pix);
    labelBt->show();

    //返回按钮
    //设置返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(labelBj);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //返回第二个场景
    connect(backBtn,&MyPushButton::clicked,[=](){
        //隐藏自身
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->backchoosescence();
        });
    });

    //显示 关卡号
    QLabel*labelGq = new QLabel(labelBj);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    labelGq->setFont(font);
    QString str = QString("Level: %1").arg(this->levelIndex);
    labelGq->setText(str);
    labelGq->setGeometry(QRect(30, this->height() - 50,130, 50)); //设置大小和位置

    dataConfig data;
    //初始化游戏数组
    for(int i = 0;i < 4;i++)
    {
        for(int j =0;j < 4;j++)
        {
            gameArray[i][j]=data.mData[this->levelIndex][i][j];
        }
    }



    //绘制金币场景
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<4;j++)
        {
            //绘制金币背景图
            QLabel *bj = new QLabel(labelBj);
            bj->setGeometry(0,0,50,50);
            bj->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            bj->move(57 + i*50,200+j*50);

            QString str;//记录金币或银币的图案路劲
            if(gameArray[i][j]==1)
            {
                str = ":/res/Coin0001.png";
            }else{
                str = ":/res/Coin0008.png";
            }




            //创建金币图片
            mycoin *mc = new mycoin(str);
            mc->posX = i;//初始化x
            mc->posY = j;//初始化y
            mc->flag = gameArray[i][j];//初始化flag
            mc->setParent(labelBj);
            mc->move(59 + i*50,204+j*50);

            coinBtn[i][j] = mc;

            connect(mc,&mycoin::clicked,[=](){
                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                mc->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改

                //延时翻动周围的金币
                QTimer::singleShot(300,this,[=](){
                    //检测右侧 并翻动
                    if(mc->posX+1 <=3)
                    {
                        coinBtn[mc->posX+1][mc->posY]->changeFlag();
                        gameArray[mc->posX+1][mc->posY] = gameArray[mc->posX+1][mc->posY]== 0 ? 1 : 0;
                    }
                    if(mc->posX-1>=0)
                    {
                        coinBtn[mc->posX-1][mc->posY]->changeFlag();
                        gameArray[mc->posX-1][mc->posY] = gameArray[mc->posX-1][mc->posY]== 0 ? 1 : 0;
                    }
                    if(mc->posY+1<=3)
                    {
                        coinBtn[mc->posX][mc->posY+1]->changeFlag();
                        gameArray[mc->posX][mc->posY+1] = gameArray[mc->posX+1][mc->posY]== 0 ? 1 : 0;
                    }
                    if(mc->posY-1>=0)
                    {
                        coinBtn[mc->posX][mc->posY-1]->changeFlag();
                        gameArray[mc->posX][mc->posY-1] = gameArray[mc->posX+1][mc->posY]== 0 ? 1 : 0;
                    }

                    //在翻完周围的金币后 判断是否全是金币，如果是 就胜利
                    this->isWin = true;
                    for(int i = 4;i<4;i++)
                    {
                        for(int j = 0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                       // qDebug()<<"游戏胜利";
                        for(int i = 4;i<4;i++)
                        {
                            for(int j = 0;j<4;j++)
                            {
                              coinBtn[i][j]->isWin = true;
                            }
                        }
                    }

                });


            });



        }
    }



}


