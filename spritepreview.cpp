#include "spritepreview.h"
#include "qpainter.h"

SpritePreview::SpritePreview(QWidget *parent)
    : QWidget{parent}
{

}

// just draw border for now to make visible
void SpritePreview::paintEvent(QPaintEvent *) {
    //    QPainter painter(this);
    //    QPen pen(Qt::black);
    //    int penWidth = 4;
    //    pen.setWidth(penWidth);
    //    painter.setPen(pen);
    //    painter.drawRect(0, 0, 130, 130);

    QPainter painter(this);
    QRect target(0, 0, 130, 130);

    if (currFrame) {
        painter.drawImage(target, currFrame->image);
    }

    else {
        int width = 10;
        int height = 10;
        QPixmap pixmap(width, height);
        pixmap.fill(QColor::fromRgb(128, 128, 128));
        QImage image = pixmap.toImage();

        painter.drawImage(target, image);
    }
}
void SpritePreview::updateDisplay(Frame* frame){
    currFrame = frame;

    repaint();
}
