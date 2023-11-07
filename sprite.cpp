#include "sprite.h"
#include "frame.h"
#include <QDebug>
#include <QColor>
#include <QMouseEvent>

Sprite::Sprite(QWidget *parent)
    : QWidget{parent}
{
    Frame* frame1 = new Frame;
    frame1->image.setPixelColor(1, 1, QColor::fromRgb(255, 0, 0));
    Frame* frame2 = new Frame;
    frame2->image.setPixelColor(1, 1, QColor::fromRgb(0, 255, 0));
    Frame* frame3 = new Frame;
    frame3->image.setPixelColor(1, 1, QColor::fromRgb(0, 0, 255));
    Frame* frame4 = new Frame;
    frame4->image.setPixelColor(1, 1, QColor::fromRgb(0, 100, 100));

    frames.append(frame1);
    frames.append(frame2);
    frames.append(frame3);
    frames.append(frame4);

    connect(timer, &QTimer::timeout, this, [this]{
        for(Frame* frame : frames){
            emit sendFramesToPreview(frame);
        }
    });
}

void Sprite::mousePressEvent(QMouseEvent * e) {
    QWidget* frame = this->childAt(e->pos());
    emit passChildSignal(frame);
}

void Sprite::updateFrame(int pixelX, int pixelY, Frame* currFrame) {
    currFrame->image.setPixelColor(pixelX, pixelY, QColor::fromRgb(0, 0, 0));
    currFrame->repaint();
}
