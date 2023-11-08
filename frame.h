#ifndef FRAME_H
#define FRAME_H

//#include <QObject>
#include <QWidget>
#include <QImage>
#include <QJsonObject>

class Frame : public QWidget
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    const QJsonObject toJson();
    void fromJson(const QJsonObject &json);
    QImage image;
    int width;
    int height;

signals:

public slots:
    void updatePixel(int pixelX, int pixelY);

};

#endif // FRAME_H
