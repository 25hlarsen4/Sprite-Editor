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

            for(int j = 0; j < frame->height; j++){

                QColor currentPixel = frame->image.pixel(i,j);

                QJsonObject pixelData;
                float red, green, blue, alpha;

                currentPixel.getRgbF(&red, &green, &blue, &alpha);

                qDebug() << "red: " << red;
                qDebug() << "green: " << green;
                qDebug() << "blue: " << blue;

                pixelData["x"] = i;
                pixelData["y"] = j;
                pixelData["red"] = red;
                pixelData["green"] = green;
                pixelData["blue"] = blue;
                pixelData["alpha"] = alpha;

                qDebug() << pixelData["alpha"];

                arrayRow.append(pixelData);

            }
            frameObject["row"] = arrayRow;

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

    QJsonObject spriteObject = serializeToJson(sprite);

    QJsonDocument jsonDoc(spriteObject);

    QByteArray jsonData = jsonDoc.toJson();

    file.write(jsonData);

    return true;
}

void File::deserializeFromJson(Sprite *sprite, QJsonObject spriteObject)
{
    sprite->frames.clear();

    QJsonArray frameArray = spriteObject["frames"].toArray();

    for (const QJsonValue & frameJson : frameArray)
    {

        QJsonObject frameObject = frameJson.toObject();

        int frameSize = frameObject["width"].toInt();
        Frame* frame = new Frame(frameSize);

        QJsonArray pixelArray = frameObject["imageData"].toArray();

        for(const QJsonValue &rowArray : pixelArray )
        {
            QJsonArray arrayRow = rowArray.toArray();
            for(const QJsonValue &pixelData : arrayRow)
            {
                int x = pixelData["x"].toDouble();
                int y = pixelData["y"].toDouble();
                int red = pixelData["red"].toDouble();
                int green = pixelData["green"].toDouble();
                int blue = pixelData["blue"].toDouble();
                int alpha = pixelData["alpha"].toDouble();
                frame->updatePixel(x, y, QColor::fromRgbF(red, green, blue, alpha));
            }

        }
        emit fileLoaded(frame);
        sprite->frames.append(frame);

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
