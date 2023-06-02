#ifndef CONFIG_H
#define CONFIG_H

// APP滚动区域样式表
#define APPSCROLLAREA_STYLE                     "QScrollBar:horizontal {height:2px; background:rgba(0,0,0,0%);}"\
                                                "QScrollBar::handle:horizontal {height:2px; background:rgba(255, 255, 255,50%); border-radius:2px;}"\
                                                "QScrollBar::add-line:horizontal {width:0px; height:0px;}"\
                                                "QScrollBar::sub-line:horizontal {width:0px; height:0px;}"\
                                                "QScrollBar::handle:horizontal:hover {height:2px; background:rgba(255, 255, 255,100%); border-radius:2px;}"\
                                                "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal {background:rgba(0,0,0,0%);}"

#define SPEAKERS_STYLE                          "QSlider{background-color:rgba(200,200,200,50%);\
                                                border-color: #bcbcbc;\
                                                }\
                                                QSlider::groove:horizontal {\
                                                background:transparent;height:1px;border-radius: 1px;left:3px;right:3px}\
                                                QSlider::handle:horizontal {\
                                                border: 0px ;\
                                                border-image:  url(:icon/Resource/icon/handle.png);\
                                                width: 30px; \
                                                margin: -15px -8px -15px -8px; \
                                                } \
                                                QSlider::add-page:horizontal{\
                                                background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc); \
                                                }\
                                                QSlider::sub-page:horizontal{ \
                                                background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3); \
                                                }"\
                                                "QSlider::groove:hover:horizontal {background:transparent;height:2px}"

#endif // CONFIG_H

