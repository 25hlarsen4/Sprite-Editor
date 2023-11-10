#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include "sprite.h"
#include "file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditor; }
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT

public:
    SpriteEditor(Sprite& sprite, File& file, QWidget *parent = nullptr);
    ~SpriteEditor();

signals:
    void changeColor(QColor);
    void sendSpriteSize(int);

private:
    Ui::SpriteEditor *ui;
    void setSpriteSize();

private slots:
    /**
     * @brief chooseColor Shows the color picker and sets the current color on the canvas
     * Source: https://www.youtube.com/watch?v=fl3q_5bxhlk
     */
    void chooseColor();

    void showCpInstructions();
    void hideCpInstructions();

public slots:

};
#endif // SPRITEEDITOR_H
