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
    connect(timer, &QTimer::timeout, this, &Sprite::updateAnimationFrame);

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
    timer->setInterval(1000 / speed);
}

void Sprite::setSpriteSize(int size){
    spriteSize = size;
    Frame* frame1 = new Frame(spriteSize);
    frame1->image.setPixelColor(1, 1, QColor::fromRgb(255, 0, 0));


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

void Sprite::updateSprite(Frame* frame){
    emit passChildSignal(frame);
    emit sendSpriteToView(this);
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

void Sprite::updateAnimationFrame() {
    // Update the frame index and the preview
    currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    emit sendFramesToPreview(frames[currentFrameIndex]);
}
