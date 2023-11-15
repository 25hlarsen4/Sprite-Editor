#include "sprite.h"
#include "frame.h"
#include <QDebug>
#include <QColor>
#include <QMouseEvent>

Sprite::Sprite(QWidget *parent)
    : QWidget{parent},currentFrameIndex(0), framesIndex(0)
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
    if(!frames.isEmpty()){
        emit sendFramesToPreview(frames[framesIndex]);
        qDebug() << "frames[index]: " << framesIndex;
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
//    frame1->image.setPixelColor(1, 1, QColor::fromRgb(255, 0, 0));
//    frame1->setFocus();
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
    timer->stop();
    qDebug() << "open sprite from file";
    qDebug() << "from openspritefromfile: " << frames.size();
    emit openSprite(this);
}

void Sprite::createNewFile( )
{
    qDebug() << "new file";

    timer->stop();

    this->frames.clear();

    Frame* frame = new Frame(spriteSize);
    frames.append(frame);

    emit passChildSignal(frame);
    emit sendSpriteToView(this);
    emit sendAllFramesToPreview(frames);

    timer->start();

}

void Sprite::updateSprite(){
    timer->start();

    qDebug() << "from sprite: " << frames.size();

    if(!frames.isEmpty()){

        emit passChildSignal(frames[0]);
        emit sendSpriteToView(this);
        emit sendAllFramesToPreview(frames);

    }

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
