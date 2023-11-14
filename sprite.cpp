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
    //connect(timer, &QTimer::timeout, this, &Sprite::updateAnimationFrame);

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
    if (framesIndex >= frames.size()) framesIndex = 0;
    if(!frames.isEmpty()){
        emit sendFramesToPreview(frames[framesIndex]);
    }
    framesIndex++;
}


void Sprite::setPreviewSpeed(int speed)
{
    if(speed > 0){
        timer->setInterval(1000 / speed);
    }else{
        timer->setInterval(1000);
    }
}

void Sprite::setSpriteSize(int size){

    spriteSize = size;
    Frame* frame1 = new Frame(spriteSize);

    frames.append(frame1);

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

void Sprite::updateSprite(){

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
