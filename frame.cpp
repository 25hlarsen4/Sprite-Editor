#include "frame.h"
#include "qpainter.h"
#include <QPixmap>
#include <QDebug>
#include <QSizePolicy>
#include <QQueue>

Frame::Frame(QWidget *parent, int spriteSize)
    : QWidget{parent}
{
    this->setFixedSize(QSize(120, 120));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFocusPolicy(Qt::ClickFocus);


    width = spriteSize;
    height = spriteSize;
    QPixmap pixmap(width, height);
    //    pixmap.fill(QColor::fromRgb(128, 128, 128));
    pixmap.fill(QColor::fromRgbF(0,0,0,0.1));
    image = pixmap.toImage();


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
}

void Frame::paintEvent(QPaintEvent *) {
    //    QImage image("C:/Users/hanna/Downloads/background.png");

    QPainter painter(this);

    int x = 3;
    int y = 3;
    int width = 110;
    int height = 110;
    QRect target(x, y, width, height);

    // draw border if has focus
    if (this->hasFocus()) {
        QPen pen(Qt::cyan);
        int penWidth = 6;
        pen.setWidth(penWidth);
        painter.setPen(pen);
        painter.drawRect(x-3, y-3, width+3, height+3);
    }

    painter.drawImage(target, image);
}

// if a widget gains focus, draw border around it
void Frame::focusInEvent(QFocusEvent *) {
    repaint();
}

// if a widget loses focus, get rid of border
void Frame::focusOutEvent(QFocusEvent *) {
    repaint();
}

void Frame::updatePixel(int pixelX, int pixelY) {
    image.setPixelColor(pixelX, pixelY, QColor::fromRgb(0, 0, 0));
    repaint();
}

// https://www.geeksforgeeks.org/flood-fill-algorithm/
void Frame::bucketFill(int pixelX, int pixelY, QColor newColor)
{
    QColor oldColor = image.pixelColor(pixelX, pixelY);

    QQueue< QPair<int, int> > pixelQueue;

    QPair<int, int> pixel(pixelX, pixelY);
    pixelQueue.enqueue(pixel);

    image.setPixelColor(pixelX,pixelY,newColor);

    while (pixelQueue.size() > 0) {

        QPair<int, int> currPixel = pixelQueue.front();
        pixelQueue.dequeue();

        int posX = currPixel.first;
        int posY = currPixel.second;

        if (isValidPixel(posX + 1, posY, oldColor, newColor)) {

            image.setPixelColor(posX + 1,posY,newColor);
            pixel.first = posX + 1;
            pixel.second = posY;
            pixelQueue.enqueue(pixel);
        }

        if (isValidPixel(posX - 1, posY, oldColor, newColor)) {
            image.setPixelColor(posX - 1,posY,newColor);
            pixel.first = posX - 1;
            pixel.second = posY;
            pixelQueue.enqueue(pixel);
        }

        if (isValidPixel(posX, posY + 1, oldColor, newColor)) {
            image.setPixelColor(posX,posY + 1,newColor);
            pixel.first = posX;
            pixel.second = posY + 1;
            pixelQueue.enqueue(pixel);
        }

        if (isValidPixel(posX, posY - 1, oldColor, newColor)) {
            image.setPixelColor(posX,posY - 1,newColor);
            pixel.first = posX;
            pixel.second = posY - 1;
            pixelQueue.enqueue(pixel);
        }
    }
}

bool Frame::isValidPixel(int pixelX, int pixelY, QColor OldColor, QColor newColor)
{
    if (pixelX < 0 || pixelX >= width || pixelY < 0 || pixelY >= height || image.pixelColor(pixelX,pixelY) != OldColor || image.pixelColor(pixelX,pixelY) == newColor)
        return false;
    return true;
}
