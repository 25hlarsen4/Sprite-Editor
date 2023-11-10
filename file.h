#ifndef FILE_H
#define FILE_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QWidget>

#include "sprite.h"

/*
 * need to save:
 * frames
*/
class File : public QWidget
{
    Q_OBJECT
public:
    File(QWidget *parent = nullptr);
    const QJsonObject toJson(Sprite *sprite);
public slots:
    bool saveFile(Sprite *sprite);
};

#endif // FILE_H
