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

    Frame(int spriteSize, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    QList<QPair<int, int>> bucketFill(int pixelX, int pixelY, QColor newColor);
    bool isValidPixel(int pixelX, int pixelY, QColor OldColor, QColor newColor);

    QImage image;
    int width;
    int height;
    void mousePressEvent(QMouseEvent *event);

    QList<QPair<int, int>> selectablePixels;

signals:
    void clicked(Frame* frame);

public slots:

    void updatePixel(int pixelX, int pixelY, QColor color);

};

#endif // FRAME_H
