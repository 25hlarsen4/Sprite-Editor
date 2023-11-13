#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qslider.h"
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
    QVBoxLayout* layout;
    //QSlider *frameCountSlider;

signals:
    void changeColor(QColor);
    void sendSpriteSize(int);
    void connectFrameSignals(Frame* frame);

private:
    Ui::SpriteEditor *ui;
    int spriteSize;
    Sprite& mySprite;
    void setSpriteSize();
    void createFileActions(Sprite &sprite);
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


    void showCpInstructions();
    void hideCpInstructions();

public slots:
    void onFrameCopied(Frame* newFrame);
    void frameSelected(Frame* frame);



};
#endif // SPRITEEDITOR_H
