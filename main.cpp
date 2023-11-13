#include "spriteeditor.h"
#include "sprite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sprite sprite;
    File file;
    SpriteEditor w(sprite, file);
    w.show();
    return a.exec();
}
