#include "file.h"

File::File(QWidget *parent)
    : QWidget{parent}
    , fileName("untitled.ssp")
{

}

const QJsonObject File::serializeToJson(Sprite *sprite)
{

    QJsonObject spriteObject;
    QJsonArray frameArray;

    // temp
    for (Frame* frame : sprite->frames)
    {

        QJsonObject frameObject;

        frameObject["width"] = frame->width;
        frameObject["height"] = frame->height;

        QJsonArray pixelArray;

        for(int i = 0; i < frame->width; i++)
        {

            QJsonArray arrayRow;

            for(int j = 0; j < frame->height; j++)
            {

                QColor currentPixel = frame->image.pixelColor(i,j);

                QJsonObject pixelData;
                int red, green, blue, alpha;

                currentPixel.getRgb(&red, &green, &blue, &alpha);

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


    fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Sprite"), "",
                                                    tr("sprite (*.ssp)"));


    qDebug() << "saving file";


    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
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
                int x = pixelData["x"].toInt();
                int y = pixelData["y"].toInt();
                int red = pixelData["red"].toInt();
                int green = pixelData["green"].toInt();
                int blue = pixelData["blue"].toInt();
                int alpha = pixelData["alpha"].toInt();
                frame->updatePixel(x, y, QColor::fromRgb(red, green, blue, alpha));
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

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));

    QJsonObject spriteObject = jsonDoc.object();

    deserializeFromJson(sprite, spriteObject);

    return true;
}
