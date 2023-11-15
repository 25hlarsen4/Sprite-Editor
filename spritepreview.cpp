#include <QImage>
#include <QDebug>
#include "spritepreview.h"
#include "qpainter.h"

SpritePreview::SpritePreview(QWidget *parent)
    : QWidget{parent}
{
    currFrame = nullptr;
}

// just draw border for now to make visible
void SpritePreview::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QRect target(0, 0, 130, 130);

    if (currFrame) {
        painter.drawImage(target, currFrame->image);
    }

//    else {
//        int width = 10;
//        int height = 10;
//        QPixmap pixmap(width, height);
//        pixmap.fill(QColor::fromRgb(128, 128, 128));
//        QImage image = pixmap.toImage();

//        painter.drawImage(target, image);
//    }
}

void SpritePreview::addFrame(Frame* frame) {
    if(frame){
        currFrame = frame;
        repaint();
    }
}
void SpritePreview::updatePreview(Frame* frame){
    if(frame){
        currFrame = frame;
        repaint();
    }
}

void SpritePreview::loadNewFrames(QList<Frame*> newFrames){
    frames = newFrames;
    currFrame = frames[0];
}
