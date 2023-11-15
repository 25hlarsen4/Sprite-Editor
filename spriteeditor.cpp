#include "spriteeditor.h"
#include "ui_spriteeditor.h"
#include "spritecanvas.h"
#include "sprite.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>
#include <QQueue>
#include <QAction>
#include <QString>

SpriteEditor::SpriteEditor(File& file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
//    , mySprite(&sprite)
    , mySprite(new Sprite)
{
    ui->setupUi(this);

    // set icons
    ui->eraseButton->setIcon(QIcon(":/icons/images/eraserIcon.jpg"));
    ui->penToolButton->setIcon(QIcon(":/icons/images/penToolIcon.jpg"));
    ui->groupSelectButton->setIcon(QIcon(":/icons/images/selectIcon.jpg"));
    ui->bucketFillButton->setIcon(QIcon(":/icons/images/bucketFillIcon.jpg"));

    layout = new QHBoxLayout(mySprite);
    layout->setSizeConstraint(layout->SetMinimumSize);

    // prevent other ui elements from taking focus from the frame widgets
    ui->addFrameButton->setFocusPolicy(Qt::NoFocus);
    ui->copyFrameButton->setFocusPolicy(Qt::NoFocus);
    ui->deleteFrameButton->setFocusPolicy(Qt::NoFocus);
    ui->colorButton->setFocusPolicy(Qt::NoFocus);
    ui->copyGroupButton->setFocusPolicy(Qt::NoFocus);
    ui->groupSelectButton->setFocusPolicy(Qt::NoFocus);
    ui->bucketFillButton->setFocusPolicy(Qt::NoFocus);
    ui->eraseButton->setFocusPolicy(Qt::NoFocus);
    ui->penToolButton->setFocusPolicy(Qt::NoFocus);
    ui->previewSpeedController->setFocusPolicy(Qt::NoFocus);
    ui->scrollArea->setFocusPolicy(Qt::NoFocus);

    // Add Frame Button
//    QPushButton *addFrameButton = new QPushButton("Add Frame", this);
//    layout->addWidget(addFrameButton); // Add the button to the layout

//    QPushButton *CopyFrameButton = new QPushButton("Copy Frame", this);
//    layout->addWidget(CopyFrameButton); // Add the button to the layout

//    QPushButton *DeleteFrameButton = new QPushButton("Delete Frame", this);
//    layout->addWidget(DeleteFrameButton); // Add the button to the layout

    // Add the sprite frames to the layout
    for (int i = 0; i < mySprite->frames.size(); ++i) {
        layout->addWidget(mySprite->frames.at(i));
    }

    ui->scrollArea->setWidget(mySprite);

    ui->cpInstructionsLabel->setVisible(false);
    ui->explanationLabel->setVisible(false);

    // connection from add frame button signal to sprite slot to create new frame
    connect(ui->addFrameButton, &QPushButton::clicked, this, &SpriteEditor::addFrame);

    // connection from sprite frame added signal to this slot to add the frame widget to layout
    // (can just access the last frame in the list)
    connect(mySprite,
            &Sprite::passChildSignal,
            ui->canvasWidget,
            &SpriteCanvas::updateDisplay);


    connect(mySprite,
            &Sprite::sendFramesToPreview,
            ui->previewWidget,
            &SpritePreview::updatePreview);

    connect(ui->previewSpeedController,
            &QAbstractSlider::valueChanged,
            mySprite,
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
            mySprite,
            &Sprite::setSpriteSize);

    connect(ui->groupSelectButton,
            &QRadioButton::toggled,
            ui->canvasWidget,
            &SpriteCanvas::updateGroupSelectState);

    connect(ui->eraseButton,
            &QRadioButton::toggled,
            ui->canvasWidget,
            &SpriteCanvas::updateEraserState);

    connect(ui->penToolButton,
            &QRadioButton::toggled,
            ui->canvasWidget,
            &SpriteCanvas::updatePenToolState);

    connect(ui->bucketFillButton,
            &QRadioButton::toggled,
            ui->canvasWidget,
            &SpriteCanvas::updateBucketFillState);

    connect(ui->copyGroupButton,
            &QPushButton::pressed,
            ui->canvasWidget,
            &SpriteCanvas::updateCopyPasteState);

//    connect(ui->copyGroupButton,
//            &QPushButton::pressed,
//            this,
//            &SpriteEditor::showCpInstructions);

    connect(ui->canvasWidget,
            &SpriteCanvas::pastingDone,
            this,
            &SpriteEditor::hideCpInstructions);

    connect(mySprite,
            &Sprite::saveSprite,
            &file,
            &File::saveFile);
    connect(mySprite,
            &Sprite::openSprite,
            &file,
            &File::loadFile);
    connect(&file,
            &File::fileLoaded,
            mySprite,
            &Sprite::updateSprite);

    connect(ui->canvasWidget,
            &SpriteCanvas::noSelectedPixelsToCopy,
            this,
            &SpriteEditor::tellUserToSelectPixels);

    connect(ui->canvasWidget,
            &SpriteCanvas::validCopy,
            this,
            &SpriteEditor::showCpInstructions);

    connect(ui->copyFrameButton, &QPushButton::clicked, this, &SpriteEditor::copyFrame);
    connect(mySprite, &Sprite::frameCopied, this, &SpriteEditor::onFrameCopied);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &SpriteEditor::deleteFrame);

    setSpriteSize();

    createFileActions(mySprite);
    createFileMenu();

    // will always start with 1 frame
    Frame* frame = mySprite->frames.at(0);
    layout->addWidget(frame);
    connect(frame, &Frame::clicked, this, &SpriteEditor::frameSelected); // Connect the clicked signal to the slot
    // give focus to the default frame
    selectedFrame = frame;
    frameSelected(selectedFrame);
    selectedFrame->setFocus();

}

void SpriteEditor::test(bool checked) {
    qDebug() << "checked: " << checked;
}



void SpriteEditor::chooseColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    QString backGroundColor("background-color: rgb(" + QString::number(color.red()) + "," + QString::number(color.green()) + "," + QString::number(color.blue()) +");");
    ui->colorButton->setStyleSheet(backGroundColor);
    emit changeColor(color);
}

void SpriteEditor::setSpriteSize()
{
    spriteSize = QInputDialog::getInt(this, tr("Sprite Editor"),
                                          tr("Please Choose A Sprite Size From 10-50!"), 10, 10, 50);
    emit sendSpriteSize(spriteSize);
}
void SpriteEditor::createFileActions(Sprite* mySprite)
{
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, mySprite, &Sprite::createNewFile);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, mySprite, &Sprite::saveSpriteToFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open file"));
    connect(openAction, &QAction::triggered, mySprite, &Sprite::openSpriteFromFile);
}
void SpriteEditor::createFileMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();

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
        "QMenuBar {"
            "background-color: rgb(75, 75, 75);"
        "}"
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

void SpriteEditor::addFrame()
{
    Frame* newFrame = new Frame(spriteSize);
    mySprite->frames.append(newFrame);
    layout->addWidget(newFrame);
    connect(newFrame, &Frame::clicked, this, &SpriteEditor::frameSelected);
    selectedFrame = newFrame;
    frameSelected(selectedFrame);
    // automatically give the new frame focus
    selectedFrame->setFocus();
}

void SpriteEditor::copyFrame() {
    if (!selectedFrame) {
        return; // No selected frame to copy
    }

    Frame* newFrame = new Frame(mySprite->spriteSize);
    newFrame->image = selectedFrame->image.copy();
    newFrame->selectablePixels = selectedFrame->selectablePixels;
    int index = layout->indexOf(selectedFrame);
    if (index == mySprite->frames.size()) {
        mySprite->frames.append(newFrame);
    } else {
        mySprite->frames.insert(index, newFrame);
    }
    layout->insertWidget(index, newFrame);
    connect(newFrame, &Frame::clicked, this, &SpriteEditor::frameSelected);
    emit mySprite->frameCopied(newFrame);
    newFrame->show();
}

void SpriteEditor::onFrameCopied(Frame* newFrame) {
    ui->previewWidget->addFrame(newFrame);
}

void SpriteEditor::frameSelected(Frame* frame) {

    if (frame == nullptr) {
        // Handle case when there is no frame
        ui->canvasWidget->setCurrentFrame(nullptr);
        return;
    }
    selectedFrame = frame;
    ui->canvasWidget->setCurrentFrame(frame);
    ui->canvasWidget->update();
}

void SpriteEditor::deleteFrame() {
    if (!selectedFrame) {
        qDebug() << "No frame selected to delete.";
        return;
    }

    int index = mySprite->frames.indexOf(selectedFrame);
    if (index == -1) {
        qDebug() << "Selected frame is not in the list.";
        return;
    }

    disconnect(selectedFrame, &Frame::clicked, this, &SpriteEditor::frameSelected);
    layout->removeWidget(selectedFrame);
    mySprite->frames.removeAt(index);
    delete selectedFrame;

    // Update selectedFrame
    if (!mySprite->frames.isEmpty()) {
        selectedFrame = mySprite->frames.first();
        frameSelected(selectedFrame);
    } else {
        selectedFrame = nullptr;
        ui->canvasWidget->setCurrentFrame(nullptr);
        ui->previewWidget->updatePreview(nullptr); // Update preview with null
    }

    ui->canvasWidget->update();
}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}

void SpriteEditor::tellUserToSelectPixels() {
    ui->explanationLabel->setVisible(true);
    // hide the explanation after 2 seconds
    QTimer::singleShot(2000, this, &SpriteEditor::hideExplanation);
}

void SpriteEditor::hideExplanation() {
    ui->explanationLabel->setVisible(false);
}




