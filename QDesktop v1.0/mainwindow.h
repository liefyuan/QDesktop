#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QDir>
#include <QTextCodec>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QGraphicsOpacityEffect>
#include <QSlider>
#include <QProcess>
struct AppObject {
    QPushButton *appobj;     // app图标
    QString program;         // 用于传入可执行程序路径
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotFinishedIpGetReply(void);      // 获取ip
    void slotFinishedIpQueryReply(void);    // ip请求完成
    void slotFinishedWeatherGetReply(void); // 获取天气数据完成

    void slotTimeoutMainTimer(void);                    // 用于更新系统时间
    void slotTimeoutAutoUpdateWeather(void);            // 用于计时自动更新天气
    void slotTimeroutExecTimer(void);                   // 用于app程序退出后计时，150ms内不得有任何操作
    void slotUpdateWeather(void);                       // 用于点击更新天气
    void slotTimerouUpdateImageTimer(void);             // 用于自动更新图片
    void slotTimeoutPageTimer(void);                    // 用于滑动页面
    void slotFinishedTimeGetReply(void);                // 获取网络时间
    void slotVolumeSpeakers();
    void slotSetSpeakerVolume();
    QString getSystemSpeakerVolume();

signals:
    void signalUpdateWeather(void);

private:
    /* 定时器 */
    QTimer *mainTimer;
    QTimer *autoUpdateWeatherTimer;
    QTimer *appExecTimer;
    QTimer *autoUpdateImageTimer;
    QTimer *pageTimer;

    /* 顶部显示 */
    QVector<QWidget *> topIcon;    //  顶部图标
    QLabel *topTimeDis;            //  顶部时间显示

    /* 左侧 */
    QLabel *displayAMorPM;         //  显示AM或PM
    QLabel *displayDate;           //  显示日期
    QLabel *displayTime;           //  显示时间
    QWidget *dateTimeDisAreaBG;    //  时间显示区域背景

    QWidget *weatherDisAreaBG;     //  区域背景
    QLabel *weatherIcon;           //  天气图标
    QLabel *displayWeather;        //  显示天气
    QLabel *displayCity;           //  显示城市
    QLabel *displayTemp;           //  显示温度
    QLabel *displayMinMaxTemp;     //  显示当天的最大温度和最小温度
    QLabel *userLabel;             //  显示用户信息
    QPushButton *speakersPushbutton;


    QWidget *displayImage;         //  用于显示相框
    QWidget *photoAlbum;           //  相册里的图片
    QVector<QString> imageArr;
    QSlider         *speakersSlider;   // 系统扬声器音量
    QWidget *centerWidget;

    /* 网络访问请求 */
    QNetworkAccessManager *NAManager;

    /* app图标 */
    QWidget *appBG;                 // 图标显示区域
    QVector<AppObject > appArr;     // 用于储存App的图标与程序路径
    QScrollArea *appBGScrollArea;   // 存放appBG

    /* 普通变量、标志位 */
    QPoint mousePressPoint;

    bool flagUpdateWeather;                             // 天气更新标志位
    bool flagAppExec;                                   // 用于app程序退出后计时，1s内不得有任何操作标志位
    int  distance;                                      // 归位的距离

    /* 私有方法 */
    void mainWindowInit(void);
    void normalVarInit(void);                           // 相关变量初始化
    void topIconInit(void);                             // 顶部图标初始化
    void datetimeDisInit(void);                         // 日期区域初始化
    void weatherDisInit(void);                          // 天气区域展示初始化
    void imageDisInit(void);                            // 左侧相册
    void networkAccessManagerInit(void);                // 网络请求初始化
    void timerInit(void);                               // 定时器初始化
    void updateWeather(void);                           // 更新天气方法
    void appIconInit(void);                             // 图标初始化
    bool eventFilter(QObject *watched, QEvent *event);  // 事件过滤器，检测
    void appIconEventFilter(QObject *watched, QEvent *event);       // APP图标事件过滤器
    void weatherIconEventFilter(QObject *watched, QEvent *event);   // 天气图标事件过滤器
    void displayImageEventFilter(QObject *watched, QEvent *event);  // 相册点击事件过滤器
};

#endif // MAINWINDOW_H
