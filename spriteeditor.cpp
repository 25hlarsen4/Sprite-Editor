#include "spriteeditor.h"
#include "ui_spriteeditor.h"
#include "spritecanvas.h"
#include "sprite.h"
#include <QVBoxLayout>
#include <QDebug>

SpriteEditor::SpriteEditor(Sprite& sprite, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(&sprite);
    layout->setSizeConstraint(layout->SetMinimumSize);
    layout->addWidget(sprite.frames.at(0));
    layout->addWidget(sprite.frames.at(1));
    layout->addWidget(sprite.frames.at(2));
    layout->addWidget(sprite.frames.at(3));

    ui->scrollArea->setWidget(&sprite);

    // connection from add frame button signal to sprite slot to create new frame

    // connection from sprite frame added signal to this slot to add the frame widget to layout
    // (can just access the last frame in the list)




    connect(&sprite,
            &Sprite::passChildSignal,
            ui->canvasWidget,
            &SpriteCanvas::updateDisplay);



    connect(ui->canvasWidget,
            &SpriteCanvas::penDrag,
            &sprite,
            &Sprite::updateFrame);

    connect(&sprite,
            &Sprite::sendFramesToPreview,
            ui->previewWidget,
            &SpritePreview::updatePreview);
}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}

