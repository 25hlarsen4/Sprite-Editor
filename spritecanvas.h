/**
 * @file spritecanvas.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The spritecanvas class is reponsible for displaying and editing individual frames of a sprite,
 * handling user inputs like mouse movements and clicks for drawing and manipulating pixels.
 *
 * @date 2023-11-14
 */
#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QWidget>
#include "frame.h"

class SpriteCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteCanvas(QWidget *parent = nullptr);

    // Override the default paintEvent with drawing of the shape
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void setCurrentFrame(Frame* frame);

private:
    Frame* currFrame;
    QRect source;
    QColor color;
    int spriteSize;
    bool groupSelect;
    QList<QPair<int, int>> selectedPixels;
    QPair<int, int> pastingAnchorPoint;
    bool clickIsForAnchorSelection;
    bool clickIsForPasting;
    bool bucketFillOn;
    bool eraserOn;
    bool penToolOn;
    Frame *selectedFrame;
    int editScreenSize;

public slots:
    void updateDisplay(QWidget* frame);
    void changeColor(QColor);
    void setSpriteSize(int);
    void updateGroupSelectState(bool);
    void updateCopyPasteState();
    void updateBucketFillState(bool);
    void updateEraserState(bool);
    void updatePenToolState(bool);
    void clearSelectedPixels();

signals:
    void pastingDone();
    void noSelectedPixelsToCopy();
    void validCopy();

};

#endif // SPRITECANVAS_H
