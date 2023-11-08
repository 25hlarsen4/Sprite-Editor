#include "spritecanvas.h"
#include "qpainter.h"
#include "frame.h"
#include <QDebug>
#include <QPixmap>
#include <QMouseEvent>

SpriteCanvas::SpriteCanvas(QWidget *parent)
    : QWidget{parent}
{
    currFrame = nullptr;
}

void SpriteCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect target(0, 0, 250, 250);

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

void SpriteCanvas::updateDisplay(QWidget* frameWidget) {
    currFrame = dynamic_cast<Frame *>(frameWidget);
    qDebug() << "update display";
    repaint();
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent * e) {
    int xPos = e->pos().x();
    int yPos = e->pos().y();

    // any x from 0 to 250/10=25 should be 0
    int pixelXCoord = xPos / 25;
    int pixelYCoord = yPos / 25;
    qDebug() << "x: " << pixelXCoord << ", y: " << pixelYCoord;


    currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, QColor::fromRgb(0, 0, 0));
    currFrame->repaint();

    repaint();
}
