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
    currColor = QColor(Qt::black);
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
    repaint();
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent * e) {
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


    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, currColor);
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
//        currFrame->floodFill(pixelXCoord, pixelYCoord, currColor);
//    }

    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, currColor);
        currFrame->repaint();

        repaint();
    }

}

void SpriteCanvas::updateCurrColor(QColor color) {
    currColor = color;

    if (groupSelect) {
        for (QPair<int, int> coords : selectedPixels) {
            currFrame->image.setPixelColor(coords.first, coords.second, currColor);
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
