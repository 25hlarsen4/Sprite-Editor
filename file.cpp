#include "file.h"

/*
 *
*/
File::File()
{

}
const bool File::saveFile(Sprite &sprite, QString fileName)
{
    QFile file("file.txt");

//    if (!saveFile.open(QIODevice::WriteOnly)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }

//    QJsonObject gameObject = toJson();
//    saveFile.write(saveFormat == Json ? QJsonDocument(gameObject).toJson()
//                                      : QCborValue::fromJsonValue(gameObject).toCbor());

    return true;
}
