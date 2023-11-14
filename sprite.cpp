#include "sprite.h"
#include "frame.h"
#include <QDebug>
#include <QColor>
#include <QMouseEvent>

Sprite::Sprite(QWidget *parent)
    : QWidget{parent},currentFrameIndex(0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Sprite::sendFrames);

}

Sprite::~Sprite(){
    for(Frame* frame : frames){
        delete frame;
    }
    frames.clear();
}

void Sprite::mousePressEvent(QMouseEvent * e)
{
    if(frames.size() != 0){
        QWidget* frame = this->childAt(e->pos());
        emit passChildSignal(frame);
        emit sendFramesToPreview(frames[0]);
    }
}


void Sprite::sendFrames()
{

    if (framesIndex >= frames.size()) framesIndex = 0;
    if(frames.size() != 0){
        emit sendFramesToPreview(frames[framesIndex]);
    }
    framesIndex++;
}


void Sprite::setPreviewSpeed(int speed)
{
    if (speed > 0)
    {
        timer->setInterval(1000 / speed);
    }

    else
    {
        timer->setInterval(1000);
    }
}

void Sprite::setSpriteSize(int size){
    spriteSize = size;
    Frame* frame1 = new Frame(spriteSize);
    emit passChildSignal(frame1);
    frame1->image.setPixelColor(1, 1, QColor::fromRgb(255, 0, 0));
//    Frame* frame2 = new Frame(spriteSize);
//    frame2->image.setPixelColor(1, 1, QColor::fromRgb(0, 255, 0));
//    Frame* frame3 = new Frame(spriteSize);
//    frame3->image.setPixelColor(1, 1, QColor::fromRgb(0, 0, 255));
//    Frame* frame4 = new Frame(spriteSize);
//    frame4->image.setPixelColor(1, 1, QColor::fromRgb(0, 100, 100));

    frames.append(frame1);
//    frames.append(frame2);
//    frames.append(frame3);
//    frames.append(frame4);

    emit passChildSignal(frame1);

    timer->setInterval(1000);
    timer->start();

    framesIndex = 0;
}

void Sprite::saveSpriteToFile()
{
    qDebug() << "save sprite to file";
    emit saveSprite(this);
}

void Sprite::openSpriteFromFile()
{
    qDebug() << "open sprite from file";
    emit openSprite(this);
}

void Sprite::createNewFile()
{

}

void Sprite::updateSprite(Frame* frame){
    emit passChildSignal(frame);
}

void Sprite::adjustFrameCount(int frameCount) {
    while (frames.size() > frameCount) {
        Frame* frame = frames.takeLast();
        delete frame;
    }

    while (frames.size() < frameCount) {
        Frame* newFrame = new Frame(spriteSize);
        frames.append(newFrame);
    }

    // Optionally, emit a signal to update the UI
    emit framesUpdated();
}
