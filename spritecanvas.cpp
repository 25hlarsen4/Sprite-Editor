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

    groupSelect = false;
    clickIsForAnchorSelection = false;
    clickIsForPasting = false;

    color = QColor::fromRgb(0, 0, 0);
}

void SpriteCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect target(0, 0, 250, 250);

    if (currFrame) {
        // make a copy of currFrame's image so we can draw on it to show pixel selection without altering the actual
        // image data
        QImage img = QImage(currFrame->image);
        painter.drawImage(target, img, source);


        // if a group pixel selection is in progress, draw semi-transparent layer over the selected pixels
        // to show they've been selected
        if (groupSelect) {
            QPainter painter2(&img);
            QPen pen = QPen(QRgba64::fromRgba(0, 255, 255, 50));
            pen.setWidth(1);
            painter2.setPen(pen);

            for (QPair<int, int> coords : selectedPixels) {
                // draw on the copied image
                painter2.drawPoint(coords.first, coords.second);
            }
            // draw the copied image onto the widget
            painter.drawImage(target, img, source);
        }
    }

    else {
        int width = 10;
        int height = 10;
        QPixmap pixmap(width, height);
        pixmap.fill(QColor::fromRgbF(0,0,0,0.1));
        QImage image = pixmap.toImage();

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++)
            {
                if(i % 2 != 0 && j % 2 != 0)
                {
                    image.setPixelColor(i, j, QColor::fromRgbF(0,0,0,0.3));
                }

                if(i % 2 == 0 && j % 2 == 0)
                {
                    image.setPixelColor(i, j, QColor::fromRgbF(0,0,0,0.3));
                }
            }
        }

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
        if(e->position().x() - 125 > 0){
            if(newX < spriteSize - 1){
                newX = newX + 1;
            }
        }
        if(e->position().y() - 125 > 0){
            if(newY < spriteSize - 1){
                newY = newY + 1;
            }
        }
    }else{
        if(source.width() < spriteSize){
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

void SpriteCanvas::changeColor(QColor newColor){
    color = newColor;

    if (groupSelect) {
        for (QPair<int, int> coords : selectedPixels) {
            currFrame->image.setPixelColor(coords.first, coords.second, color);
        }

        currFrame->repaint();
        repaint();

        // "unselect" all pixels
        selectedPixels.clear();
        repaint();
    }
}


void SpriteCanvas::setSpriteSize(int size){
    spriteSize = size;
    source.setRect(0, 0, spriteSize, spriteSize);
}

void SpriteCanvas::updateGroupSelectState() {
    groupSelect = !groupSelect;
}

void SpriteCanvas::updateCopyPasteState() {
    qDebug() << "pick anchor selection";
    clickIsForAnchorSelection = true;
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent * e) {
    int xPos = e->pos().x();
    int yPos = e->pos().y();

    int pixelXCoord = source.x() + xPos/(250/source.width());
    int pixelYCoord = source.y() + yPos/(250/source.height());

    // if we're selecting pixels
    if (groupSelect) {
        QPair<int, int> pixelCoords = qMakePair(pixelXCoord, pixelYCoord);

        // only "select" the pixel if it is "selectable" (has been drawn on before and is not already selected)
        if (currFrame->selectablePixels.contains(pixelCoords) && !selectedPixels.contains(pixelCoords)) {
            selectedPixels.append(pixelCoords);
        }

//        if (selectedPixels.contains(pixelCoords) == false) {
//            selectedPixels.append(pixelCoords);
//        }

        // give a visual cue that it's selected
        repaint();
    }

    // if we're drawing
    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, color);
        currFrame->repaint();

        repaint();

        // this pixel is now selectable because it's been drawn on
        QPair<int, int> pixelCoords = qMakePair(pixelXCoord, pixelYCoord);
        if (!currFrame->selectablePixels.contains(pixelCoords)) {
            currFrame->selectablePixels.append(pixelCoords);
        }
    }
}



void SpriteCanvas::mousePressEvent(QMouseEvent * e) {
    int xPos = e->pos().x();
    int yPos = e->pos().y();

    int pixelXCoord = source.x() + xPos/(250/source.width());
    int pixelYCoord = source.y() + yPos/(250/source.height());

    // if we're selecting pixels
    if (groupSelect) {
        if (clickIsForAnchorSelection) {
            pastingAnchorPoint = qMakePair(pixelXCoord, pixelYCoord);
            qDebug() << "anchor point: " << pastingAnchorPoint;
            clickIsForAnchorSelection = false;
            clickIsForPasting = true;
        }
        else if (clickIsForPasting) {
            QPair<int, int> pastePoint = qMakePair(pixelXCoord, pixelYCoord);
            qDebug() << "paste point: " << pastePoint;
            clickIsForPasting = false;

            // now define the translation
            int xTranslation = pastePoint.first - pastingAnchorPoint.first;
            qDebug() << "x translation: " << xTranslation;
            int yTranslation = pastePoint.second - pastingAnchorPoint.second;
            qDebug() << "y translation: " << yTranslation;

            for (QPair<int, int> coords : selectedPixels) {
                qDebug() << "original point: " << coords;
                QColor pixelColor = currFrame->image.pixelColor(coords.first, coords.second);

                int resultX = coords.first + xTranslation;
                int resultY = coords.second + yTranslation;
                QPair<int, int> resPoint = qMakePair(resultX, resultY);
                qDebug() << "result point: " << resPoint;

                // make sure it's a valid pixel position
                if (resultX >= 0 && resultX < source.width() && resultY >= 0 && resultY < source.height()) {
                    currFrame->image.setPixelColor(resultX, resultY, pixelColor);

                    // this pixel is now selectable because it's been drawn on
                    QPair<int, int> pixelCoords = qMakePair(resultX, resultY);
                    if (!currFrame->selectablePixels.contains(pixelCoords)) {
                        currFrame->selectablePixels.append(pixelCoords);
                    }
                }

            }

            currFrame->repaint();

            selectedPixels.clear();

            repaint();

            emit pastingDone();
        }


        // otherwise just add to group
        else {
            QPair<int, int> pixelCoords = qMakePair(pixelXCoord, pixelYCoord);

            // only "select" the pixel if it is "selectable" (has been drawn on before and is not already selected)
            if (currFrame->selectablePixels.contains(pixelCoords) && !selectedPixels.contains(pixelCoords)) {
                selectedPixels.append(pixelCoords);
            }

            // give a visual cue that it's selected
            repaint();
        }
    }

    //    else if (floodFill) {
    //        // call flood fill algorithm
    //        currFrame->floodFill(pixelXCoord, pixelYCoord, color);
    //    }

    // if we're drawing
    else {
        currFrame->image.setPixelColor(pixelXCoord, pixelYCoord, color);
        currFrame->repaint();

        repaint();

        // this pixel is now selectable because it's been drawn on
        QPair<int, int> pixelCoords = qMakePair(pixelXCoord, pixelYCoord);
        if (!currFrame->selectablePixels.contains(pixelCoords)) {
            currFrame->selectablePixels.append(pixelCoords);
        }
    }

}
