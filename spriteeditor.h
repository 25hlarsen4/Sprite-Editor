/**
 * @file spriteeditor.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A8: Sprite Editor Implementation
 *
 * The spriteeditor class is reponsible for functions on the ui application like addFrame, copyFrame, saveFiles etc.
 *
 * @date 2023-11-14
 */
#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include "QtWidgets/qboxlayout.h"
#include "sprite.h"
#include "file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditor; }
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT

public:
    SpriteEditor(File& file, QWidget *parent = nullptr);
    ~SpriteEditor();
    QHBoxLayout* layout;

signals:
    void changeColor(QColor);
    void sendSpriteSize(int);
    void connectFrameSignals(Frame* frame);

private:
    Ui::SpriteEditor *ui;
    int spriteSize;
    Sprite* mySprite;

    void setSpriteSize();
    void createFileActions(Sprite* sprite);
    void createFileMenu();

    QMenu *fileMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAct;
    void addFrame();
    Frame* selectedFrame;

private slots:
    /**
     * @brief chooseColor Shows the color picker and sets the current color on the canvas
     * Source: https://www.youtube.com/watch?v=fl3q_5bxhlk
     */
    void chooseColor();
    void copyFrame();
    void deleteFrame();

    void addFramesToLayout(Sprite *sprite);


    void showCpInstructions();
    void hideCpInstructions();

    void test(bool);

    void tellUserToSelectPixels();

public slots:

    void onFrameCopied(Frame* newFrame);
    void frameSelected(Frame* frame);
    void hideExplanation();



};
#endif // SPRITEEDITOR_H
