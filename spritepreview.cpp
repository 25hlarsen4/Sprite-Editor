#include "spritepreview.h"
#include "qpainter.h"

SpritePreview::SpritePreview(QWidget *parent)
    : QWidget{parent}
{

}

// just draw border for now to make visible
void SpritePreview::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen pen(Qt::black);
    int penWidth = 4;
    pen.setWidth(penWidth);
    painter.setPen(pen);
    painter.drawRect(0, 0, 130, 130);
}
