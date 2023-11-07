#include "frame.h"
#include "qpainter.h"
#include <QPixmap>
#include <QDebug>
#include <QSizePolicy>

Frame::Frame(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(QSize(120, 120));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFocusPolicy(Qt::ClickFocus);


    int width = 10;
    int height = 10;
    QPixmap pixmap(width, height);
    pixmap.fill(QColor::fromRgb(128, 128, 128));
    image = pixmap.toImage();
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
