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

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();

    framesIndex = 0;


    connect(timer, &QTimer::timeout, this, &Sprite::sendFrames);

}

void Sprite::mousePressEvent(QMouseEvent * e)
{
    QWidget* frame = this->childAt(e->pos());
    emit passChildSignal(frame);
    emit sendFramesToPreview(frames[0]);
}

void Sprite::updateFrame(int pixelX, int pixelY, Frame* currFrame)
{
    currFrame->image.setPixelColor(pixelX, pixelY, QColor::fromRgb(0, 0, 0));
    currFrame->repaint();
}

void Sprite::sendFrames()
{

    if (framesIndex == frames.size()) framesIndex = 0;

    emit sendFramesToPreview(frames[framesIndex]);

    framesIndex++;
}
const QJsonObject Sprite::toJson()
{

    QJsonObject json;
    QJsonArray frameArray;

    for (Frame* frame : frames)
        frameArray.append(frame->toJson());

    json["frames"] = frameArray;

    return json;
}
void Sprite::fromJson(const QJsonObject &json)
{
//    frames.clear();
//    const QJsonArray framesArray = json["frames"].toArray();
//    for (const QJsonValue &frame : framesArray)
//        frames.append(Frame::fromJson(frame.toObject()));
}
