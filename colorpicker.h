#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QColorDialog>

class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = nullptr);
    QColorDialog *colorPicker;

signals:

public slots:
    void setVisible();

};

#endif // COLORPICKER_H
