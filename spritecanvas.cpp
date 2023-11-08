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
    source.setRect(0, 0, 10, 10);
}

void SpriteCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect target(0, 0, 250, 250);

    if (currFrame) {
        qDebug() << source;
        painter.drawImage(target, currFrame->image, source);
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

void SpriteCanvas::wheelEvent(QWheelEvent * e){
    int newSize = source.width();
    int newX = source.x();
    int newY = source.y();
    if(e->angleDelta().y() > 0){
        if(source.width() > 1){
            newSize = source.width() - 1;
        }
        newX = e->position().x()/25 - newSize/2 + 1;
        newY = e->position().y()/25 - newSize/2 + 1;
    }else{
        if(source.width() < 10){
            newSize = source.width() + 1;
        }
        if(newX > 0){
            newX = newX - 1;
        }
        if(newY > 0){
            newY = newY - 1;
        }
    }
    source.setRect(newX, newY, newSize, newSize);
    currFrame->repaint();
    repaint();
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
