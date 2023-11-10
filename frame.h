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

    QImage image;
    int width;
    int height;

    QList<QPair<int, int>> selectablePixels;

signals:

public slots:
    void updatePixel(int pixelX, int pixelY, const QColor& color);

};

#endif // FRAME_H
