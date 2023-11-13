#include "sprite.h"
#include "frame.h"
#include <QDebug>
#include <QColor>
#include <QMouseEvent>

Sprite::Sprite(QWidget *parent)
    : QWidget{parent}
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
    QWidget* frame = this->childAt(e->pos());
    emit passChildSignal(frame);
    emit sendFramesToPreview(frames[0]);
}


void Sprite::sendFrames()
{

    if (framesIndex == frames.size()) framesIndex = 0;

    emit sendFramesToPreview(frames[framesIndex]);

    framesIndex++;
}

void Sprite::setPreviewSpeed(int speed)
{
    timer->setInterval(1000 - 900*speed*0.01);
}

void Sprite::setSpriteSize(int size){
    spriteSize = size;
    Frame* frame1 = new Frame(spriteSize);
    frame1->image.setPixelColor(1, 1, QColor::fromRgb(255, 0, 0));
    Frame* frame2 = new Frame(spriteSize);
    frame2->image.setPixelColor(1, 1, QColor::fromRgb(0, 255, 0));
    Frame* frame3 = new Frame(spriteSize);
    frame3->image.setPixelColor(1, 1, QColor::fromRgb(0, 0, 255));
    Frame* frame4 = new Frame(spriteSize);
    frame4->image.setPixelColor(1, 1, QColor::fromRgb(0, 100, 100));

    frames.append(frame1);
    frames.append(frame2);
    frames.append(frame3);
    frames.append(frame4);

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
