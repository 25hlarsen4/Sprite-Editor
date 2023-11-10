#include "file.h"

/*
 *
*/

File::File(QWidget *parent)
    : QWidget{parent}
{

}

const QJsonObject File::toJson(Sprite *sprite)
{

    QJsonObject spriteObject;
    QJsonArray frameArray;
    // temp
    for (Frame* frame : sprite->frames){

        QJsonObject frameObject;

        frameObject["width"] = frame->width;
        frameObject["height"] = frame->height;

        QJsonArray pixelArray;

        for(int i = 0; i < frame->width; i++){

            QJsonArray arrayRow;

            for(int j = 0; i < frame->height; i++){

                QColor currentPixel = frame->image.pixel(i,j);

                QJsonObject pixelData;

                pixelData["x"] = i;
                pixelData["y"] = j;
                pixelData["red"] = qRed(currentPixel.value());
                pixelData["green"] = qGreen(currentPixel.value());
                pixelData["blue"] = qBlue(currentPixel.value());

                arrayRow.append(pixelData);

            }

            pixelArray.append(arrayRow);

        }

        frameObject["imageData"] = pixelArray;

        frameArray.append(frameObject);
    }

    spriteObject["frames"] = frameArray;

    return spriteObject;
}

bool File::saveFile(Sprite *sprite)
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Sprite"), "",
                                                    tr("sprite (*.ssp);All Files (*)"));

    qDebug() << "saving file";


    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject spriteObject = toJson(sprite);

    QJsonDocument jsonDoc(spriteObject);

    QByteArray jsonData = jsonDoc.toJson();

    file.write(jsonData);

    return true;
}

