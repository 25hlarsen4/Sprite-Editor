#include "spritecanvas.h"
#include "qpainter.h"
#include "frame.h"
#include <QDebug>
#include <QPixmap>
#include <QMouseEvent>
#include <QRgba64>

SpriteCanvas::SpriteCanvas(QWidget *parent)
    : QWidget{parent}
{
    currFrame = nullptr;

    groupSelect = false;

    source.setRect(0, 0, 10, 10);
    color = QColor::fromRgb(0, 0, 0);

}

void SpriteCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect target(0, 0, 250, 250);

    if (currFrame) {
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
        // Change from hardcoded 10 to some image size
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
    repaint();
}


void SpriteCanvas::mouseMoveEvent(QMouseEvent * e) {
    int xPos = e->pos().x();
    int yPos = e->pos().y();

    // any x from 0 to 250/10=25 should be 0

    int pixelXCoord = source.x() + xPos/(250/source.width());
    int pixelYCoord = source.y() + yPos/(250/source.height());


    if (groupSelect) {
        selectedPixels.append(qMakePair(pixelXCoord, pixelYCoord));


        // give a visual cue that it's selected (just make white for now)
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, QColor::fromRgb(255, 255, 255));
        currFrame->repaint();


        repaint();
    }


    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, color);
        currFrame->repaint();

        repaint();
    }
}



void SpriteCanvas::mouseReleaseEvent(QMouseEvent * e) {
    int xPos = e->pos().x();
    int yPos = e->pos().y();

    // any x from 0 to 250/10=25 should be 0
    int pixelXCoord = xPos / 25;
    int pixelYCoord = yPos / 25;

    if (groupSelect) {
        selectedPixels.append(qMakePair(pixelXCoord, pixelYCoord));

        // give a visual cue that it's selected (just make white for now)
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, QColor::fromRgb(255, 255, 255));
        currFrame->repaint();

        repaint();
    }

//    else if (floodFill) {
//        // call flood fill algorithm
//        currFrame->floodFill(pixelXCoord, pixelYCoord, color);
//    }

    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, olor);
        currFrame->repaint();

        repaint();
    }

}

void SpriteCanvas::updateCurrColor(QColor newColor) {
    color = newColor;

    if (groupSelect) {
        for (QPair<int, int> coords : selectedPixels) {
            currFrame->image.setPixelColor(coords.first, coords.second, color);
        }

        currFrame->repaint();
        repaint();

        // "unselect all pixels"
        selectedPixels.clear();
    }
}

void SpriteCanvas::updateGroupSelectState() {
    groupSelect = !groupSelect;
}
