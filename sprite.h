#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QTimer>

#include "frame.h"

class Sprite : public QWidget
{
    Q_OBJECT
public:
    explicit Sprite(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);

    // made this an array of ptrs because QObjects are not copyable, must work with pointers instead
    QList<Frame*> frames;
    QTimer *timer;
    int framesIndex;

protected:

private:

signals:
    void passChildSignal(QWidget* frame);
    void sendFramesToPreview(Frame* frame);

public slots:
    void updateFrame(int pixelX, int pixelY, Frame* currFrame);
    void sendFrames();

};

#endif // SPRITE_H
