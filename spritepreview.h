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

    /**
     * @brief paintEvent draws the pixels of the selected frame on the ui.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Helper function for copy frame in spriteeditor. Add the copied frame to the preview
     * @param frame
     */
    void addFrame(Frame* frame);

private:
    // keep these in sync with sprite's frame list
    QList<Frame*> frames;
    Frame *currFrame;

signals:
public slots:

    /**
     * @brief updatePreview updates the frame that is currently being previewed.
     * @param frame
     */
    void updatePreview(Frame* frame);

    /**
     * @brief loadNewFrames updates the preview with the frames
     */
    void loadNewFrames(QList<Frame*>);

};

#endif // SPRITEPREVIEW_H
