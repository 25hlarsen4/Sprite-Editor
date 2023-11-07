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

private:
    Ui::SpriteEditor *ui;

public slots:

};
#endif // SPRITEEDITOR_H
