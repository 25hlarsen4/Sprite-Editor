#include "spriteeditor.h"
#include "ui_spriteeditor.h"
#include "spritecanvas.h"
#include "sprite.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>

SpriteEditor::SpriteEditor(Sprite& sprite, File& file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(&sprite);
    layout->setSizeConstraint(layout->SetMinimumSize);

    ui->scrollArea->setWidget(&sprite);

    ui->cpInstructionsLabel->setVisible(false);

    // connection from add frame button signal to sprite slot to create new frame

    // connection from sprite frame added signal to this slot to add the frame widget to layout
    // (can just access the last frame in the list)
    connect(&sprite,
            &Sprite::passChildSignal,
            ui->canvasWidget,
            &SpriteCanvas::updateDisplay);


    connect(&sprite,
            &Sprite::sendFramesToPreview,
            ui->previewWidget,
            &SpritePreview::updatePreview);

    connect(ui->previewSpeedController,
            &QAbstractSlider::valueChanged,
            &sprite,
            &Sprite::setPreviewSpeed);

    connect(ui->colorButton,
            &QPushButton::clicked,
            this,
            &SpriteEditor::chooseColor);

    connect(this,
            &SpriteEditor::changeColor,
            ui->canvasWidget,
            &SpriteCanvas::changeColor);

    connect(this,
            &SpriteEditor::sendSpriteSize,
            ui->canvasWidget,
            &SpriteCanvas::setSpriteSize);

    connect(this,
            &SpriteEditor::sendSpriteSize,
            &sprite,
            &Sprite::setSpriteSize);



    connect(ui->groupSelectCheckBox,
            &QCheckBox::clicked,
            ui->canvasWidget,
            &SpriteCanvas::updateGroupSelectState);

    connect(ui->copyGroupButton,
            &QPushButton::pressed,
            ui->canvasWidget,
            &SpriteCanvas::updateCopyPasteState);

    connect(ui->copyGroupButton,
            &QPushButton::pressed,
            this,
            &SpriteEditor::showCpInstructions);

    connect(ui->canvasWidget,
            &SpriteCanvas::pastingDone,
            this,
            &SpriteEditor::hideCpInstructions);

    connect(ui->saveButton,
            &QPushButton::clicked,
            &sprite,
            &Sprite::saveSpriteToFile);
    connect(&sprite,
            &Sprite::saveSprite,
            &file,
            &File::saveFile);
    connect(ui->openButton,
            &QPushButton::clicked,
            &sprite,
            &Sprite::openSpriteFromFile);
    connect(&sprite,
            &Sprite::openSprite,
            &file,
            &File::loadFile);
    connect(&file,
            &File::fileLoaded,
            &sprite,
            &Sprite::updateSprite);



    setSpriteSize();

    layout->addWidget(sprite.frames.at(0));
    layout->addWidget(sprite.frames.at(1));
    layout->addWidget(sprite.frames.at(2));
    layout->addWidget(sprite.frames.at(3));
}

void SpriteEditor::chooseColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    emit changeColor(color);
}

void SpriteEditor::setSpriteSize()
{
    int spriteSize = QInputDialog::getInt(this, tr("Sprite Editor"),
                                          tr("Please Choose A Sprite Size From 10-50!"), 10, 10, 50);
    emit sendSpriteSize(spriteSize);
}

void SpriteEditor::showCpInstructions() {
    ui->cpInstructionsLabel->setVisible(true);
}

void SpriteEditor::hideCpInstructions() {
    ui->cpInstructionsLabel->setVisible(false);
}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}




