#include "colorpicker.h"
#include <colorpicker.h>
#include <QColorDialog>

ColorPicker::ColorPicker(QWidget *parent)
    : QWidget{parent}
{
    colorPicker = new QColorDialog(this);

}

void ColorPicker::setVisible() {
    colorPicker->setVisible(true);
}
