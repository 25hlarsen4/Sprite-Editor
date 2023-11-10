#include "file.h"

/*
 *
*/

File::File(QWidget *parent)
    : QWidget{parent}
{

}

const QJsonObject File::serializeToJson(Sprite *sprite)
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
                                                    tr("sprite (*.ssp)"));

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

void File::deserializeFromJson(Sprite *sprite, QJsonObject spriteObject)
{

    QJsonArray frameArray = spriteObject["frames"].toArray();

    for (const QJsonValue & frame : frameArray)
    {
        Frame frame;
        QJsonObject frameObject = frame.toObject();

    }

}


bool File::loadFile(Sprite* sprite)
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("sprite (*.ssp)"));

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));

    QJsonObject spriteObject = jsonDoc.object();

    deserializeFromJson(sprite, spriteObject);

    return true;
}
