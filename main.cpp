#include "spriteeditor.h"
#include "sprite.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sprite sprite;
    SpriteEditor w(sprite);
    w.show();
    return a.exec();
}
