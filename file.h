#ifndef FILE_H
#define FILE_H
#include <QJsonObject>
#include <QFile>

#include "sprite.h"

/*
 * need to save:
 * frames
*/
class File
{
public:
    File();
    const bool saveFile(Sprite &sprite, QString fileName);
};

#endif // FILE_H
