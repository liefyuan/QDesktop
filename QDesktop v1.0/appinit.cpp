#include "appinit.h"
#include "config.h"
void MainWindow::appIconInit(void) {
    appArr.clear();
    /* 初始化: app区域及滚动区域 */
    appBGScrollArea = new QScrollArea(this);
    appBG = new QWidget(appBGScrollArea);
    appBG->setGeometry(0, 0, (float)1080/800*this->geometry().width(), (float)370/480*this->geometry().height());
    appBG->setStyleSheet("QWidget{background-color:transparent}");
    appBGScrollArea->setGeometry((float)260/800*this->geometry().width(),(float)55/480*this->geometry().height(),
                                 (float)540/800*this->geometry().width(),(float)390/480*this->geometry().height());   
    appBGScrollArea->setWidget(appBG);
    appBGScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                // 关闭垂直滚动条
    appBGScrollArea->setStyleSheet("QScrollArea{background-color:transparent}");
    appBGScrollArea->horizontalScrollBar()->setStyleSheet(APPSCROLLAREA_STYLE);
    appBGScrollArea->setFrameShape(QScrollArea::NoFrame);

    struct AppObject appObj;

    /* 初始化app图标 */
    QPushButton *appMusic = new QPushButton(appBG);
    appMusic->setGeometry(0, 0, (float)250/800*this->geometry().width(),
                          (float)120/480*this->geometry().height());   // 音乐
    appMusic->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconMusic);outline:none}"
                            "QPushButton:hover {border-image: url(Resource/icon/iconMusic_hover)}");
    appObj.program = "../QMusicPlayer/QMusicPlayer";
    appObj.appobj=appMusic;
    appArr.append(appObj);



    QPushButton *appVideo = new QPushButton(appBG);
    appVideo->setGeometry((float)255/800*this->geometry().width(), 0,
                          (float)120/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 视频
    appVideo->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconVideo);outline:none}"
                            "QPushButton:hover {border-image: url(Resource/icon/iconVideo_hover)}");
    appObj.program = "../QMediaPlayer/QMediaPlayer";
    appObj.appobj=appVideo;
    appArr.append(appObj);

    QPushButton *appPicture = new QPushButton(appBG);
    appPicture->setGeometry((float)380/800*this->geometry().width(), 0, (float)150/800*this->geometry().width(), // 图片浏览器
                            (float)120/480*this->geometry().height());   // 图片
    appPicture->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconPicture);outline:none}"
                              "QPushButton:hover {border-image: url(Resource/icon/iconPicture_hover)}");
    appObj.program = "../QImageViewer/QImageViewer";
    appObj.appobj=appPicture;
    appArr.append(appObj);

    QPushButton *appWeb = new QPushButton(appBG);
    appWeb->setGeometry(0, (float)125/480*this->geometry().height(),
                        (float)375/800*this->geometry().width(), (float)120/480*this->geometry().height());   // web浏览器
    appWeb->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconWebview);outline:none}"
                          "QPushButton:hover {border-image: url(Resource/icon/iconWebview_hover)}");
    appObj.program = "../QWebBrowser/QWebBrowser";
    appObj.appobj=appWeb;
    appArr.append(appObj);

    QPushButton *appFolder = new QPushButton(appBG);
    appFolder->setGeometry((float)380/800*this->geometry().width(), (float)125/480*this->geometry().height(),
                           (float)150/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 文件
    appFolder->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconFile);outline:none}"
                             "QPushButton:hover {border-image: url(Resource/icon/iconFile_hover)}");
    appObj.program = "../QFileView/QFileView";
    appObj.appobj=appFolder;
    appArr.append(appObj);

    QPushButton *appCalculator = new QPushButton(appBG);
    appCalculator->setGeometry(0, (float)250/480*this->geometry().height(),
                               (float)120/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 计算器
    appCalculator->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconCalculator);outline:none}"
                                 "QPushButton:hover {border-image: url(Resource/icon/iconCalculator_hover)}");
    appObj.program = "../QCalculator/QCalculator";
    appObj.appobj=appCalculator;
    appArr.append(appObj);

    QPushButton *appCamera = new QPushButton(appBG);
    appCamera->setGeometry((float)125/800*this->geometry().width(), (float)250/480*this->geometry().height(),
                             (float)120/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 相机
    appCamera->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconCamera);outline:none}"
                               "QPushButton:hover {border-image: url(Resource/icon/iconCamera_hover)}");
    appObj.program = "../QCamera/QCamera";
    appObj.appobj=appCamera;
    appArr.append(appObj);

    QPushButton *appWeather = new QPushButton(appBG);
    appWeather->setGeometry((float)250/800*this->geometry().width(), (float)250/480*this->geometry().height(),
                            (float)280/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 天气
    appWeather->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconWeather);outline:none}"
                                  "QPushButton:hover {border-image: url(Resource/icon/iconWeather_hover)}");
    appObj.program = "../QOnlineWeather/QOnlineWeather";
    appObj.appobj=appWeather;
    appArr.append(appObj);

    QPushButton *appCalendar = new QPushButton(appBG);
    appCalendar->setGeometry((float)540/800*this->geometry().width(), 0,
                            (float)262/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 日历
    appCalendar->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconCalendar);outline:none}"
                              "QPushButton:hover {border-image: url(Resource/icon/iconCalendar_hover)}");
    appObj.program = "../QCalendar/QCalendar";
    appObj.appobj=appCalendar;
    appArr.append(appObj);

    QPushButton *appRecorder = new QPushButton(appBG);
    appRecorder->setGeometry((float)807/800*this->geometry().width(), 0,
                         (float)263/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 录音
    appRecorder->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconRecorder);outline:none}"
                           "QPushButton:hover {border-image: url(Resource/icon/iconRecorder_hover)}");
    appObj.program = "../QRecorder/QRecorder";
    appObj.appobj=appRecorder;
    appArr.append(appObj);

    QPushButton *appTemperature = new QPushButton(appBG);
    appTemperature->setGeometry((float)807/800*this->geometry().width(), (float)125/480*this->geometry().height(),
                             (float)129/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 温度
    appTemperature->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconTemperature);outline:none}"
                              "QPushButton:hover {border-image: url(Resource/icon/iconTemperature_hover)}");
    appObj.program = "../QTemperature/QTemperature";
    appObj.appobj=appTemperature;
    appArr.append(appObj);

    QPushButton *appNotepad = new QPushButton(appBG);
    appNotepad->setGeometry((float)540/800*this->geometry().width(), (float)125/480*this->geometry().height(),
                         (float)128/800*this->geometry().width(), (float)120/480*this->geometry().height());       // 记事本
    appNotepad->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconNotepad);outline:none}"
                           "QPushButton:hover {border-image: url(Resource/icon/iconNotepad_hover)}");
    appObj.program = "../QNotepad/QNotepad";
    appObj.appobj=appNotepad;
    appArr.append(appObj);

    QPushButton *appLed = new QPushButton(appBG);
    appLed->setGeometry((float)540/800*this->geometry().width(), (float)250/480*this->geometry().height(),
                                (float)128/800*this->geometry().width(), (float)120/480*this->geometry().height());   // LED
    appLed->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconLed);outline:none}"
                                  "QPushButton:hover {border-image: url(Resource/icon/iconLed_hover)}");
    appObj.program = "../QLed/QLed";
    appObj.appobj=appLed;
    appArr.append(appObj);

    QPushButton *appReader = new QPushButton(appBG);
    appReader->setGeometry((float)673/800*this->geometry().width(), (float)125/480*this->geometry().height(),
                            (float)129/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 阅读
    appReader->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconReader);outline:none}"
                              "QPushButton:hover {border-image: url(Resource/icon/iconReader_hover)}");
    appObj.program = "../QReader/QReader";
    appObj.appobj=appReader;
    appArr.append(appObj);

    QPushButton *appClock = new QPushButton(appBG);
    appClock->setGeometry((float)673/800*this->geometry().width(), (float)250/480*this->geometry().height(),
                           (float)129/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 时钟
    appClock->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconClock);outline:none}"
                             "QPushButton:hover {border-image: url(Resource/icon/iconClock_hover)}");
    appObj.program = "../QClock/QClock";
    appObj.appobj=appClock;
    appArr.append(appObj);

    QPushButton *appAutotest = new QPushButton(appBG);
    appAutotest->setGeometry((float)807/800*this->geometry().width(), (float)250/480*this->geometry().height(),
                         (float)129/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 终端
    appAutotest->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconAutotest);outline:none}"
                           "QPushButton:hover {border-image: url(Resource/icon/iconAutotest_hover)}");
    appObj.program = "../QAutotest/QAutotest";
    appObj.appobj=appAutotest;
    appArr.append(appObj);

    QPushButton *appUnknow = new QPushButton(appBG);
    appUnknow->setGeometry((float)940/800*this->geometry().width(), (float)125/480*this->geometry().height(),
                         (float)129/800*this->geometry().width(), (float)120/480*this->geometry().height());   // 未知应用
    appUnknow->setStyleSheet("QPushButton {border-image: url(Resource/icon/iconUnknow);outline:none}"
                           "QPushButton:hover {border-image: url(Resource/icon/iconUnknow_hover)}");
    appObj.program = "../iconUnknow/iconUnknow";
    appObj.appobj=appUnknow;
    appArr.append(appObj);

    for(int i = 0; i< appArr.count(); i++)
    {
        appArr[i].appobj->installEventFilter(this); // 安装事件过滤器
    }

    centerWidget = new QWidget(this);
    centerWidget->setGeometry((float)200/800*this->geometry().width(),(float)220/480*this->geometry().height(),
                             (float)400/800*this->geometry().width(),(float)110/480*this->geometry().height());
    centerWidget->setStyleSheet("border-image:transparent;background-color:rgba(40,40,40,50%);border-radius: 20px;");

    speakersSlider = new QSlider(Qt::Horizontal,centerWidget);
    centerWidget->hide();
    speakersSlider->setGeometry((float)25/800*this->geometry().width(),(float)30/480*this->geometry().height(),
                                (float)350/800*this->geometry().width(),(float)50/480*this->geometry().height());
    speakersSlider->setStyleSheet(SPEAKERS_STYLE);
#ifdef __arm__
    speakersSlider->setRange(80,127);
    //因为linux是通过开启进程来控制音量，已经设置阻塞，所以当松手滑块时才开始设置音量
    connect(speakersSlider,SIGNAL(sliderReleased()),this,SLOT(slotSetSpeakerVolume()));
#else
    speakersSlider->setRange(0,100);
    connect(speakersSlider,SIGNAL(valueChanged(int)),this,SLOT(slotSetSpeakerVolume()));
#endif
}

