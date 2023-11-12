#include "spriteeditor.h"
#include "ui_spriteeditor.h"
#include "spritecanvas.h"
#include "sprite.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>
#include <QQueue>
#include <QAction>

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
    connect(ui->bucketFillBox,
            &QCheckBox::clicked,
            ui->canvasWidget,
            &SpriteCanvas::updateBucketFillState);

    connect(&sprite,
            &Sprite::saveSprite,
            &file,
            &File::saveFile);
    connect(&sprite,
            &Sprite::openSprite,
            &file,
            &File::loadFile);
    connect(&file,
            &File::fileLoaded,
            &sprite,
            &Sprite::updateSprite);

    setSpriteSize();

    createFileActions(sprite);
    createFileMenu();

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
void SpriteEditor::createFileActions(Sprite &sprite)
{
//    newAct = new QAction(tr("&New"), this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Create a new file"));
//    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, &sprite, &Sprite::saveSpriteToFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open file"));
    connect(openAction, &QAction::triggered, &sprite, &Sprite::openSpriteFromFile);
}
void SpriteEditor::createFileMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    //fileMenu->addAction(exitAct);

//    editMenu = menuBar()->addMenu(tr("&Edit"));
//    editMenu->addAction(undoAct);
//    editMenu->addAction(redoAct);
//    editMenu->addSeparator();
//    editMenu->addAction(cutAct);
//    editMenu->addAction(copyAct);
//    editMenu->addAction(pasteAct);
//    editMenu->addSeparator();

//    helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAct);
//    helpMenu->addAction(aboutQtAct);

    QString  menuStyle(
        "QMenuBar { \
                background-color: rgb(75, 75, 75); \
        }"
        "QMenuBar::item {"
        "color: rgb(255, 255, 255)"
        "}"
        "QMenuBar::item:selected{"
        "background-color: rgb(50, 50, 50);"
        "}"
        "QMenu::item{"
        "background-color: rgb(75, 75, 75);"
        "color: rgb(255, 255, 255);"
        "}"
        "QMenu::item:selected{"
        "background-color: rgb(50, 50, 50);"
        "color: rgb(255, 255, 255);"
        "}"
        );
    this->setStyleSheet(menuStyle);
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




