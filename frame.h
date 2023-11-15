/**
 * @file frame.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The frame class is reponsible for displaying and interacting with sprite frames, handling rendering, mouse events,
 * and pixel updates. It provides functionalities like bucket filling and updating individual pixels, essential
 * for editing and visualizing sprite animations or images.
 *
 * @date 2023-11-14
 */
#ifndef FRAME_H
#define FRAME_H

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
    // if ever changing focus between frames, clear selected pixels
    void focusLost();

public slots:

    void updatePixel(int pixelX, int pixelY, QColor color);

};

#endif // FRAME_H
