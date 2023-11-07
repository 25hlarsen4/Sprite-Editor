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

private:
    // keep these in sync with sprite's frame list
    QList<Frame*> frames;

signals:

};

#endif // SPRITEPREVIEW_H
