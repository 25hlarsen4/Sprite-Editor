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
    void bucketFill(int pixelX, int pixelY, QColor newColor);
    bool isValidPixel(int pixelX, int pixelY, QColor OldColor, QColor newColor);
<<<<<<< HEAD
=======

>>>>>>> refs/heads/Bracken
    QImage image;
    int width;
    int height;

    QList<QPair<int, int>> selectablePixels;

signals:

public slots:
<<<<<<< HEAD
    void updatePixel(int pixelX, int pixelY, QColor color);
=======
    void updatePixel(int pixelX, int pixelY, const QColor color);
>>>>>>> refs/heads/Bracken

};

#endif // FRAME_H
