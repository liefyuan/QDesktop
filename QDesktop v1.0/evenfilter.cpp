#include "evenfilter.h"
#include <QProcess>
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    appIconEventFilter(watched, event);                     // app图标的事件过滤器
    weatherIconEventFilter(watched, event);                 // 天气图标事件过滤器
    displayImageEventFilter(watched, event);                // 相册点击后开启相册程序
    return QWidget::eventFilter(watched,event);             // 将事件传递给父类

}

void MainWindow::appIconEventFilter(QObject *watched, QEvent *event)
{
    static QPoint point;                                       // 记录按下的点
    static int offsetx;                                        // 用于计算移动的距离
    static QDateTime n_dateTime;                               // 用于点击图标时计时
    static QDateTime now_dateTime;                             // 用释放图标时计时
    static QGraphicsOpacityEffect  *opacityEffect = new QGraphicsOpacityEffect(); // 设置图标的不透明度

    for(int i = 0; i < appArr.count(); i++){
        if(watched == appArr[i].appobj){
            switch (event->type()) {
            case QEvent::MouseButtonPress:
                centerWidget->setVisible(false);
                point.setX(cursor().pos().x());     // 记录按下时的x坐标
                appArr[i].appobj->setGraphicsEffect(opacityEffect);
                opacityEffect->setOpacity(0.8);     // 按下图标80%透明
                n_dateTime = QDateTime::currentDateTime();
                break;
            case QEvent::Leave:
                opacityEffect->setOpacity(1);       // 鼠标离开后图标为完全不透明
                break;
            case QEvent::MouseMove:
                if(!flagAppExec)
                    return;                         // 在此返回，程序退出1s后，过滤掉阻塞掉的点击事件，防止滑动
                /* 计算页面移动的距离 */
                pageTimer->stop();
                offsetx = cursor().pos().x() - point.x();
                appBGScrollArea->horizontalScrollBar()->setValue(appBGScrollArea->horizontalScrollBar()->value() - offsetx);
                point.setX(cursor().pos().x());      // 重新采样
                break;
            case QEvent::MouseButtonRelease:
                pageTimer->start(25);
                distance = appBGScrollArea->horizontalScrollBar()->value(); // 获取当前滚动条的值
                now_dateTime = QDateTime::currentDateTime();
                opacityEffect->setOpacity(1);         // 松开鼠标后为完全不透明
                /* 如果正在滑动屏幕，那么也不进入程序 */
                if(appBGScrollArea->horizontalScrollBar()->value() != 0 &&
                        appBGScrollArea->horizontalScrollBar()->value() != appBGScrollArea->horizontalScrollBar()->maximum())
                    return;
                /* 判断按下是否小于150ms，长按是不会进入程序 */
                if(n_dateTime.msecsTo(now_dateTime) < 150 && flagAppExec == true){
                    flagAppExec = false;
                    this->hide();
                    QProcess appProcess;
                    appProcess.start(appArr[i].program);
                    appProcess.waitForFinished(-1);
                    appExecTimer->start(1000);       // 程序退出1s后，过滤掉阻塞掉的点击事件，防止再次进入
                    this->show();
                }

                break;
            default:
                break;
            }
        }
    }
}

void MainWindow::weatherIconEventFilter(QObject *watched, QEvent *event)
{
    if (watched == weatherIcon){
        switch (event->type()) {
        case QEvent::Enter:
            weatherIcon->setToolTip("点我刷新天气");
            break;
        case QEvent::MouseButtonPress:
            slotUpdateWeather();    // 点击后更新天气
            break;
        default:
            break;
        }
    }
}

void MainWindow::displayImageEventFilter(QObject *watched, QEvent *event)
{
    static QDateTime n_dateTime;                               // 用于点击时计时
    static QDateTime now_dateTime;                             // 用释放图标时计时
    if (watched == displayImage){
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            n_dateTime = QDateTime::currentDateTime();
            break;
        case QEvent::MouseButtonRelease:
            now_dateTime = QDateTime::currentDateTime();
            if(n_dateTime.msecsTo(now_dateTime) < 150 && flagAppExec == true){ // 判断按下是否小于150ms，长按是不会进入程序的
                flagAppExec = false;
                this->hide();
                QProcess appProcess;
                appProcess.start("../QPictureViewer/QPictureViewer");
                appProcess.waitForFinished(-1);
                appExecTimer->start(1000);       // 程序退出1000ms后，过滤掉阻塞掉的点击事件，防止再次进入
                this->show();
            }
            break;
        default:
            break;
        }
    }
}

