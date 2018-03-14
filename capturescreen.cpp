#include "capturescreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

CaptureScreen::CaptureScreen(QWidget *parent) : QWidget(parent)
{
    initWindow();
    loadBackgroundPixmap();
}

CaptureScreen::~CaptureScreen()
{
}


void CaptureScreen::initWindow(){
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowActive|Qt::WindowFullScreen);
}


void CaptureScreen::loadBackgroundPixmap(){
    m_loadPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    m_screenheight = m_loadPixmap.height();
    m_screenwidth = m_loadPixmap.width();
}


void CaptureScreen::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        m_isMousePress = true;
        m_beginPoint = event->pos();
    }
    return QWidget::mousePressEvent(event);
}

void CaptureScreen::mouseMoveEvent(QMouseEvent *event){
    if(m_isMousePress){
        m_endPoint = event->pos();
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void CaptureScreen::mouseReleaseEvent(QMouseEvent *event){
    m_endPoint = event->pos();
    m_isMousePress = false;
    return QWidget::mouseReleaseEvent(event);
}

void CaptureScreen::paintEvent(QPaintEvent *event){
    m_painter.begin(this);

    QColor shadowColor = QColor(0,0,0,100);
    m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
    m_painter.drawPixmap(0,0,m_loadPixmap);
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);

    if(m_isMousePress){
        QRect selectRect = getRect(m_beginPoint, m_endPoint);
        m_capturePixmap = m_loadPixmap.copy(selectRect);
        m_painter.drawPixmap(selectRect.topLeft(), m_capturePixmap);
        m_painter.drawRect(selectRect);
    }

    m_painter.end();
}

void CaptureScreen::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Escape){
        close();
    }
    if(event->key()==Qt::Key_Return|| event->key()==Qt::Key_Enter||event->key()==Qt::Key_Space){
        signalCompleteCapture(m_capturePixmap);
        close();
    }
}

QRect CaptureScreen::getRect(const QPoint &beginPoint, const QPoint &endPoint){
    int x, y, width, height;
    width = qAbs(beginPoint.x()-endPoint.x());
    height = qAbs(beginPoint.y()-endPoint.y());
    x = beginPoint.x()<endPoint.x()?beginPoint.x():endPoint.x();
    y = beginPoint.y()<endPoint.y()?beginPoint.y():endPoint.y();

    QRect selectedRect = QRect(x,y,width,height);
    if(selectedRect.width()==0)
        selectedRect.setWidth(1);
    if(selectedRect.height()==0)
        selectedRect.setHeight(1);

    return selectedRect;
}
