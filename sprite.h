/**
 * @file sprite.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The sprite class manages sprite animations by handling a collection of Frame objects and
 * controlling their display and updates.
 *
 * @date 2023-11-14
 */
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
    ~Sprite();
    Sprite& operator=(const Sprite& other);

    // made this an array of ptrs because QObjects are not copyable, must work with pointers instead
    QList<Frame*> frames;
    QTimer *timer;
    int framesIndex;
    int spriteSize;
    int currentFrameIndex;

    /**
     * @brief mousePressEvent will trigger when the mouse is clicked on the sprite. It emits signals to pass the updated information of this frame to other parts of the application
     * and update the sprite preview.
     */
    void mousePressEvent(QMouseEvent *);

    /**
     * @brief adjustFrameCount checks if the number of frames in the sprite to match the specified frameCount.
     * It adds new frames or deletes excess frames to ensure the total number of frames equals frameCount.
     * It emits a signal to update the user interface with these changes.
     * @param frameCount
     */
    void adjustFrameCount(int frameCount);

protected:

private:


signals:
    void passChildSignal(QWidget* frame);
    /*
     * This signal sends a frame to the preview.
    */
    void sendFramesToPreview(Frame* frame);
    void frameCopied(Frame* newFrame);
    void framesUpdated();
    void saveSprite(Sprite*);
    void openSprite(Sprite*);
    void sendSpriteToView(Sprite*);
    void sendAllFramesToPreview(QList<Frame*>);
    void setCanvasSize(int);

public slots:

    /**
     * @brief sendFrames cycles through the sprite's frames, emitting a signal to display each frame in sequence for to preview the animation on top right.
     */
    void sendFrames();

    /**
     * @brief setPreviewSpeed adjusts the preview speed by setting the interval of a timer based on the provided speed value.
     */
    void setPreviewSpeed(int);

    /**
     * @brief setSpriteSize set the size of the frames when the program starts.
     */
    void setSpriteSize(int);

    /**
     * @brief saveSpriteToFile emits saveSprite signal when the save button is clicked.
     */
    void saveSpriteToFile();

    /**
     * @brief openSpriteFromFile emits openSprite signal when the open button is clicked.
     */
    void openSpriteFromFile();

    /**
     * @brief createNewFile indicates we are getting a new frame.
     */
    void createNewFile();

    /**
     * @brief updateSprite indicates to update sprite.
     */
    void updateSprite();

};

#endif // SPRITE_H
