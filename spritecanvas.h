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

    void mouseReleaseEvent(QMouseEvent *);


    void wheelEvent(QWheelEvent *);

private:
    Frame* currFrame;
    QRect source;
    QColor color;
    bool groupSelect;
    QList<QPair<int, int>> selectedPixels;


signals:

public slots:
    void updateDisplay(QWidget* frame);
    void updateCurrColor(QColor color);
    void updateGroupSelectState();

};

#endif // SPRITECANVAS_H
