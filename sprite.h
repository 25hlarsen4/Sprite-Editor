#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>

#include "frame.h"

class Sprite : public QWidget
{
    Q_OBJECT
public:
    explicit Sprite(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    const QJsonObject toJson();
    void fromJson(const QJsonObject &json);

    // made this an array of ptrs because QObjects are not copyable, must work with pointers instead
    QList<Frame*> frames;
    QTimer *timer;

    int framesIndex;

protected:

private:

signals:
    void passChildSignal(QWidget* frame);

    /*
     * This signal sends a frame to the preview.
    */
    void sendFramesToPreview(Frame* frame);

public slots:

    /*
     * emits a signal to spritepreview of the frame at the current index to be previewed.
     * Increment index or set to 0 if current index is greater than number of frames.
    */
    void sendFrames();

};

#endif // SPRITE_H
