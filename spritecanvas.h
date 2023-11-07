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

private:
    Frame* currFrame;

signals:
    void penDrag(int pixelX, int pixelY, Frame* currFrame);

public slots:
    void updateDisplay(QWidget* frame);

};

#endif // SPRITECANVAS_H
