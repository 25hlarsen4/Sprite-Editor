#ifndef FILE_H
#define FILE_H
#include <QJsonObject>

#include "sprite.h"

/*
 * need to save:
 * frames
*/
class File
{
public:
    File();
    const QJsonObject saveFile(Sprite &sprite);
};

#endif // FILE_H
