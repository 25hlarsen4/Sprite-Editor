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
#ifndef SPRITEPREVIEW_H
#define SPRITEPREVIEW_H

#include <QWidget>
#include "frame.h"

class SpritePreview : public QWidget
{
    Q_OBJECT
public:
    explicit SpritePreview(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void addFrame(Frame* frame);

private:
    // keep these in sync with sprite's frame list
    QList<Frame*> frames;
    Frame *currFrame;

signals:
public slots:
    /*
     * updates the frame that is currently being previewed.
    */
    void updatePreview(Frame* frame);
    void loadNewFrames(QList<Frame*>);

};

#endif // SPRITEPREVIEW_H
