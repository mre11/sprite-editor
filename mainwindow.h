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
    Q_ENUMS(ToolBrush)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum ToolBrush
    {
        Darken,
        Lighten,
        Brush,
        Eraser,
        EyeDrop,
        Bucket
    };

public slots:
    void updateAnimation();
    void toolBrushClicked();
    void processMouseClick(QPoint pt);
    void updateCanvas();
    void toggleGridDisplay();
    void primaryColorClicked();

    // Process when the user clicks new, open, save, or exit.
    void fileMenuItemClicked();

private:
    Ui::MainWindow *ui;
    SpriteFrameCollection frames;
    QTimer animationTimer;
    SpriteFrame *currentFrame;
    ToolBrush brush;
    QColor currentColor;

    int canvasWidth;
    int canvasHeight;
};

#endif // MAINWINDOW_H
