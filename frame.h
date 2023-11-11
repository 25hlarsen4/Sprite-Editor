#ifndef FRAME_H
#define FRAME_H

//#include <QObject>
#include <QWidget>
#include <QImage>
#include <QJsonObject>

class Frame : public QWidget
{
    Q_OBJECT
public:
    Frame(int spriteSize, QWidget *parent);
    void paintEvent(QPaintEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void bucketFill(int pixelX, int pixelY, QColor newColor);
    bool isValidPixel(int pixelX, int pixelY, QColor OldColor, QColor newColor);
    QImage image;
    int width;
    int height;

    QList<QPair<int, int>> selectablePixels;

signals:

public slots:
    void updatePixel(int pixelX, int pixelY, QColor color);

};

#endif // FRAME_H
