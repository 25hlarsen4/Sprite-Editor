/**
 * @file spritepreview.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The spritepreview class is reponsible for displaying the preview of the frame animation on the top right corner
 * of the ui.
 *
 * @date 2023-11-14
 */
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
    }
    else {
        currFrame = nullptr;
    }
    repaint();

}

void SpritePreview::loadNewFrames(QList<Frame*> newFrames){

    frames = newFrames;
    currFrame = frames[0];

}
