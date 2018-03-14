#ifndef CAPTURESCREEN_H
#define CAPTURESCREEN_H

#include <QWidget>
#include <QPainter>

class CaptureScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CaptureScreen(QWidget *parent = nullptr);
    ~CaptureScreen();

Q_SIGNALS:
    void signalCompleteCapture(QPixmap captureImage);
private:
    bool m_isMousePress;
    QPixmap m_loadPixmap, m_capturePixmap;
    int m_screenwidth;
    int m_screenheight;
    QPoint m_beginPoint, m_endPoint;
    QPainter m_painter;

    void initWindow();
    void loadBackgroundPixmap();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
signals:

public slots:
};

#endif // CAPTURESCREEN_H
