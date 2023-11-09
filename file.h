#ifndef FILE_H
#define FILE_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>

#include "sprite.h"

/*
 * need to save:
 * frames
*/
class File
{
public:
    File();
    const QJsonObject toJson(Sprite *sprite);
    bool saveFile(Sprite &sprite);
};

#endif // FILE_H
