#ifndef FRAME_H
#define FRAME_H

//#include <QObject>
#include <QWidget>
#include <QImage>

class Frame : public QWidget
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    QImage image;

signals:

public slots:
    void updatePixel(int pixelX, int pixelY);

};

#endif // FRAME_H
