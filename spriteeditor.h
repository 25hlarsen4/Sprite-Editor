#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditor; }
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT

public:
    SpriteEditor(Sprite& sprite, QWidget *parent = nullptr);
    ~SpriteEditor();

signals:
    void changeColor(QColor);

private:
    Ui::SpriteEditor *ui;

private slots:
    /**
     * @brief chooseColor Shows the color picker and sets the current color on the canvas
     * Source: https://www.youtube.com/watch?v=fl3q_5bxhlk
     */
    void chooseColor();

public slots:

};
#endif // SPRITEEDITOR_H
