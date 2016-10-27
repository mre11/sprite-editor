// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "spriteframecollection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateAnimation();
    void processMouseClick(QPoint pt);
    void updateCanvas();

private:
    Ui::MainWindow *ui;
    SpriteFrameCollection frames;
    QTimer animationTimer;
    SpriteFrame *currentFrame;

    void toggleGridDisplay();
};

#endif // MAINWINDOW_H
