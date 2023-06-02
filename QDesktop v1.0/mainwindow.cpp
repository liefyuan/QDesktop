#include "mainwindow.h"
#include "weather.h"
#include "config.h"
#include <QDesktopWidget>
#include <QApplication>
#define   DEFAULT_IMAGE_FILEPATH   "Resource/images"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 主窗口初始化 */
    mainWindowInit();

    /* 普通变量初始化 */
    normalVarInit();

    /* 顶部图标初始化 */
    topIconInit();

    /* 时间、日期显示初始化 */
    datetimeDisInit();

    /* 天气初始化 */
    weatherDisInit();

    /* image */
    imageDisInit();

    /* 网络访问请求初始化 */
    networkAccessManagerInit();

    /* 定时器初始化 */
    timerInit();

    /* app初始化 */
    appIconInit();

    /* 信号、槽函数连接 */
    connect(this, SIGNAL(signalUpdateWeather()), this, SLOT(slotUpdateWeather()));
}

MainWindow::~MainWindow()
{
    /* 定时器 */
    delete mainTimer;
    delete autoUpdateWeatherTimer;

    /* app */
    appArr.clear();

    delete appBG;

    /* 网络 */
    delete NAManager;

    /* 顶部 */
    qDeleteAll(topIcon);
    topIcon.clear();
    delete topTimeDis;

    /* 左侧 */
    delete displayAMorPM;
    delete displayDate;
    delete displayTime;
    delete dateTimeDisAreaBG;

    delete weatherIcon;
    delete displayWeather;
    delete displayCity;
    delete displayTemp;
    delete displayMinMaxTemp;
    delete weatherDisAreaBG;

    delete displayImage;
    imageArr.clear();
}


/*
 * 私有方法
 */
void MainWindow::mainWindowInit(void) {
    this->setGeometry(0,0, 800, 480);
    //this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QMainWindow {border-image: url(Resource/background/bgDesktop_0);}");
    this->installEventFilter(this); // 安装事件过滤器

    userLabel = new QLabel(this);
    userLabel->setGeometry((float)10/800*this->geometry().width(),(float)5/480*this->geometry().height(),
                           (float)25/800*this->geometry().width(),(float)25/800*this->geometry().width());
    userLabel->setStyleSheet("QLabel {border-image: url(Resource/icon/user.png);}");

    speakersPushbutton = new QPushButton(this);
    speakersPushbutton->setGeometry((float)750/800*this->geometry().width(),0,(float)50/800*this->geometry().width(),(float)50/800*this->geometry().width());
    speakersPushbutton->setStyleSheet("border-image:url(Resource/icon/speaker.png);outline:none");
    connect(speakersPushbutton,SIGNAL(clicked()),this,SLOT(slotVolumeSpeakers()));
}

void MainWindow::normalVarInit(void) {
    /* 标志位 */
    flagAppExec             = true;
    flagUpdateWeather       = false;
}

void MainWindow::topIconInit(void) {
    QFont font;

    /* 时间显示初始化 */
    topTimeDis = new QLabel(this);
    topTimeDis->setGeometry((float)360/800*this->geometry().width(), (float)2/480*this->geometry().height(),
                            (float)80/800*this->geometry().width(), (float)20/480*this->geometry().height());
    topTimeDis->setStyleSheet("QLabel {color: white;background: transparent}");
    topTimeDis->setAlignment(Qt::AlignCenter);
    topTimeDis->setText(QTime::currentTime().toString().mid(0, 8));
    font.setPointSize((float)14/800*this->geometry().width());
    topTimeDis->setFont(font);
}

void MainWindow::datetimeDisInit(void) {
    QFont font;
    /* 区域背景显示 */
    dateTimeDisAreaBG = new QWidget(this);
    dateTimeDisAreaBG->setGeometry((float)20/800*this->geometry().width(), (float)60/480*this->geometry().height(),
                                   (float)220/800*this->geometry().width(), (float)120/480*this->geometry().height());
    dateTimeDisAreaBG->setStyleSheet("QWidget {border-image: url(Resource/background/bgTime);"
                                     "background-color: rgba(0, 0, 0, 0%);}");

    /* 时间 */
    QTime currentTime = QTime::currentTime();
    displayTime = new QLabel(this);
    displayTime->setGeometry((float)20/800*this->geometry().width(), (float)60/480*this->geometry().height(),
                             (float)180/800*this->geometry().width(), (float)80/480*this->geometry().height());
    displayTime->setStyleSheet("QLabel { color: white;background: transparent}");
    displayTime->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    displayTime->setText(currentTime.toString().mid(0, 5));
    font.setPointSize((float)48/800*this->geometry().width());
    displayTime->setFont(font);

    /* AM?  PM? */
    displayAMorPM = new QLabel(this);
    displayAMorPM->setGeometry((float)200/800*this->geometry().width(), (float)100/480*this->geometry().height(),
                               (float)40/800*this->geometry().width(), (float)40/480*this->geometry().height());
    displayAMorPM->setStyleSheet("QLabel {color: white;background: transparent}");
    displayAMorPM->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    font.setPointSize((float)15/800*this->geometry().width());
    displayAMorPM->setFont(font);

    if (12 <= currentTime.hour())
        displayAMorPM->setText("PM");
    else
        displayAMorPM->setText("AM");

    /* 日期 */
    displayDate = new QLabel(this);
    displayDate->setGeometry((float)30/800*this->geometry().width(), (float)140/480*this->geometry().height(),
                             (float)200/800*this->geometry().width(), (float)40/480*this->geometry().height());
    displayDate->setStyleSheet("QLabel { color: white;background: transparent}");
    displayDate->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    displayDate->setText(QDate::currentDate().toString("MMMM dd dddd"));
    font.setPointSize((float)12/800*this->geometry().width());
    displayDate->setFont(font);
}

void MainWindow::imageDisInit(void) {
    imageArr.clear();

    /* 扫描目录添加文件 */
    QDir dir(DEFAULT_IMAGE_FILEPATH);
    if (dir.exists()) {

        QStringList filter;             // 定义一个过滤器
        filter << "*.png";              // 添加需要扫描的文件类型
        QFileInfoList files = dir.entryInfoList(filter, QDir::Files);

        for (int i = 0; i < files.count(); i++) {
            QString path = files.at(i).filePath();
            imageArr.append(path);      //  将image路径添加到数组
        }
    }

    photoAlbum = new QWidget(this);
    photoAlbum->setGeometry((float)20/800*this->geometry().width(), (float)315/480*this->geometry().height(),
                            (float)220/800*this->geometry().width(), (float)150/480*this->geometry().height());

    /* 判断是否为空 */
    if (!imageArr.isEmpty())
        photoAlbum->setStyleSheet("QWidget{border-image:url("+ imageArr[0] +")}");


    /* 对象初始化，相册外框 */
    displayImage = new QWidget(this);
    displayImage->setGeometry((float)20/800*this->geometry().width(), (float)315/480*this->geometry().height(),
                              (float)220/800*this->geometry().width(), (float)150/480*this->geometry().height());
    displayImage->setStyleSheet("QWidget {border:10px; border-style:outset; padding:0px; margin:0px;"
                                "border-color: rgba(255, 255, 255, 50%);}");
    displayImage->installEventFilter(this); // 安装事件过滤器，当点击相册时，打开相册程序
}

void MainWindow::timerInit(void) {
    /* 实例化 */
    mainTimer               = new QTimer(this);
    autoUpdateWeatherTimer  = new QTimer(this);
    appExecTimer            = new QTimer(this);
    autoUpdateImageTimer    = new QTimer(this);
    pageTimer               = new QTimer(this);

    /* 信号与槽函数连接 */
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(slotTimeoutMainTimer()));
    connect(autoUpdateWeatherTimer, SIGNAL(timeout()), this, SLOT(slotTimeoutAutoUpdateWeather()));
    connect(appExecTimer, SIGNAL(timeout()), this, SLOT(slotTimeroutExecTimer()));
    connect(autoUpdateImageTimer, SIGNAL(timeout()), this, SLOT(slotTimerouUpdateImageTimer()));
    connect(pageTimer, SIGNAL(timeout()), this, SLOT(slotTimeoutPageTimer()));

    /* 开启定时器 */
    mainTimer->start(1000);   // 1s秒更新一次
    autoUpdateWeatherTimer->start(1000 * 60 * 20);  // 20分钟更新一次天气显示
    if (2 <= imageArr.count()) // 判读当前是否扫描到了多张image 如果小于2则不用开启
        autoUpdateImageTimer->start(100);
}
/* 更新时间和日期 */
void MainWindow::slotTimeoutMainTimer(void) {
    QTime currentTime = QTime::currentTime();
    QString time = currentTime.toString().mid(0, 5);

    /* 设置时间 */
    displayTime->setText(time);
    time = currentTime.toString().mid(0, 8);
    topTimeDis->setText(time);

    /* AM? PM? */
    if (12 <= currentTime.hour())
        displayAMorPM->setText("PM");
    else
        displayAMorPM->setText("AM");

    /* 更新日期 */
    displayDate->setText(QDate::currentDate().toString("MMMM dd dddd"));

}

void MainWindow::slotTimerouUpdateImageTimer()
{
    static int i   = 0;
    static qreal j = 0.4;
    static int k   = 0;
    static QGraphicsOpacityEffect  *opacityEffect = new QGraphicsOpacityEffect(); // 设置图标的不透明度
    i++;
    if(i == 30){ // 7s
        k++;
        if(k == imageArr.count()){
            k = 0;
        }
        j = 0.2;
        photoAlbum->setGraphicsEffect(opacityEffect);
        photoAlbum->setStyleSheet("QWidget{border-image:url("+ imageArr[k] +")}");
    }
    if(i == 50) // 10s
        i = 0;

    if (j >= 0.2)
        j = j + 0.1;
    opacityEffect->setOpacity(j);
}
/* 自动更新天气 */
void MainWindow::slotTimeoutAutoUpdateWeather(void) {
    /* 如果当前正处于更新状态 则退出 因为手动更新可能会与自动更新时间上存在冲突 */
    if (!flagUpdateWeather)
        return;

    flagUpdateWeather = false;
    slotUpdateWeather();//更新天气
}
/* 防止阻塞后误操作 */
void MainWindow::slotTimeroutExecTimer()
{
    appExecTimer->stop();
    flagAppExec = true;
}

/* 更新天气 */
void MainWindow::slotUpdateWeather(void) {
    displayCity->setText("正在定位...");
    slotFinishedIpGetReply();
}
/* 页面滑动计算 */
void MainWindow::slotTimeoutPageTimer()
{
    static int distanceStep = (float)80/800*this->geometry().width();
    if(appBGScrollArea->horizontalScrollBar()->value()<appBGScrollArea->horizontalScrollBar()->maximum()/2){
        distance = distance - distanceStep;
        if(distance <= 0)
        {
            pageTimer->stop();
            distance = 0;
        }
        appBGScrollArea->horizontalScrollBar()->setValue(distance);
    }else{

        if(distance >= appBGScrollArea->horizontalScrollBar()->maximum())
        {
            pageTimer->stop();
            distance = appBGScrollArea->horizontalScrollBar()->maximum();
        }
        distance = distance + distanceStep;
        appBGScrollArea->horizontalScrollBar()->setValue(distance);
    }

}

void MainWindow::slotVolumeSpeakers()
{
#ifdef __arm__
    if(!flagAppExec)
        return;
    if( getSystemSpeakerVolume().length() > 0){
        QString volume = getSystemSpeakerVolume();
        speakersSlider->setValue(volume.toInt());  //先重新获取一下扬声器音量，防止用户在其他地方有修改过音量
    }else{
        //TODO
    }
#endif
    if(centerWidget->isVisible())
        centerWidget->setVisible(false);
    else
        centerWidget->setVisible(true);
}

QString MainWindow::getSystemSpeakerVolume()
{
#ifdef __arm__
    QProcess pro;
    QString cmd = "Resource/cmd/getSystemSpeakerVolume.sh";
    pro.start(cmd);
    //pro.start("echo $(amixer get Speaker |grep -E \"Left:\" |awk '{print $4}')");
    pro.waitForFinished(-1);
    QString x = pro.readAll();
    return x.left(x.length()-1);
#else
    return "";
#endif
}

void MainWindow::slotSetSpeakerVolume()
{
#ifdef __arm__
    QString volume = getSystemSpeakerVolume();
    if( volume.length()>0){//如果获取到值
        int val = speakersSlider->value();
        if(val <=80)
            val = 0;
        QString cmd = "amixer set Speaker " + QString::number(val) ;
        QProcess pro;
        pro.start(cmd);
        pro.waitForFinished(-1);// 阻塞
    }else{

    }
#endif
}

