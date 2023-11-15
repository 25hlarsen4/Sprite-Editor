/**
 * @file frame.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The frame class is responsible for displaying and interacting with sprite frames, handling rendering, mouse events,
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

    /**
     * @brief This function creates an empty frame on the ui.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief focusInEvent draws a frame around the selected frame, indicating it is being selected in ui.
     */
    void focusInEvent(QFocusEvent *);

    /**
     * @brief focusOutEvent remove the frame around the original selected frame as it is no longer selected.
     */
    void focusOutEvent(QFocusEvent *);

    /**
     * @brief bucketFill fills the pixels inside a boundary to a new color selected by user.
     * @param pixelX
     * @param pixelY
     * @param newColor
     * @return
     */
    QList<QPair<int, int>> bucketFill(int pixelX, int pixelY, QColor newColor);

    /**
     * @brief A helper method  for bucketFill to ensure that color operations are applied only to the intended pixels within the frame.
     * @param pixelX
     * @param pixelY
     * @param OldColor
     * @param newColor
     * @return
     */
    bool isValidPixel(int pixelX, int pixelY, QColor OldColor, QColor newColor); //private?

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
