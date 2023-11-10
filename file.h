#ifndef FILE_H
#define FILE_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QWidget>

#include "sprite.h"
#include "frame.h"

/*
 * need to save:
 * frames
*/
class File : public QWidget
{
    Q_OBJECT
public:

    File(QWidget *parent = nullptr);

    const QJsonObject serializeToJson(Sprite *sprite);
    void deserializeFromJson(Sprite *sprite, QJsonObject spriteObject);
signals:
    void fileLoaded(Frame* frame);

public slots:

    bool saveFile(Sprite*);
    bool loadFile(Sprite*);

};

#endif // FILE_H
