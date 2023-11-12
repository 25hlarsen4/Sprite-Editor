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

    /**
     * @brief This method serializes a sprite object into a json object
     * with all necessary data to recreate the sprite object.
     * @param sprite - the sprite object to be serialized.
     * @return JsonObject - The json object where sprite data will be serialized.
     */
    const QJsonObject serializeToJson(Sprite *sprite);

    /**
     * @brief This method deserializes a json object that represents a
     *  sprite object, extracts the necessary data and updates the sprite
     *  object with the deserialized data.
     * @param sprite - The sprite object to be updated with deserialized data.
     * @param spriteObject - the json object containing data to be deserialized.
     */
    void deserializeFromJson(Sprite *sprite, QJsonObject spriteObject);

private:
    QString fileName;

signals:

    /**
     * @brief fileLoaded - This signal is sent to the sprite object when the file
     * is loaded so the sprite knows to update the sprite information.
     * @param frame signal sends the new frame to the sprite.
     */
    void fileLoaded(Frame* frame);

public slots:

    /**
     * @brief saveFile -This method shows a file dialog box that allows the user
     * to enter a file name. A json document is initialized with the json sprite object
     * and a byte array is initialized with the json document. A QFile is created with
     * the user's file name and the byte array is written to the document.
     * @return true if file has been saved.
     */
    bool saveFile(Sprite*);

    /**
     * @brief loadFile - This method shows a file dialog box that the user can choose
     * a file from. The file is read in to a byte array and a json document is created
     * from it. Then a json object is created from the document and deserialized.
     * @return true if the file has been loaded.
     */
    bool loadFile(Sprite*);

};

#endif // FILE_H
