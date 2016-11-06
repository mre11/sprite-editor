// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStringListModel>
#include "newspritedialog.h"
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

    // Enum for distinguishing which tool is being used.
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
    // tools
    void updateAnimation();

    // Sets the frames per second for the animation interval.
    void setAnimationTimerInterval(int fps);

    // Sets the current tool brush.
    void toolBrushClicked();

    // Collects the QPoint at which the user clicked.
    void processMouseClick(QPoint pt);

    // Updates the canvas by redrawing
    void updateCanvas();

    // Sets the toggle grid display on or off.
    void toggleGridDisplay();

    // Displays a color picker dialog for changing colors.
    void primaryColorClicked();

    // Handles file menu click events
    void fileMenuItemClicked();

    // Handles export menu click
    void exportMenuItemClicked();

private slots:

    // Adds frames to the frame list view
    void addFrameClicked();

    // Resets the current frame
    void resetFrameClicked();

    // Deletes the current selected frame
    void deleteFrameClicked();

    // Displays the current frame on the canvas.
    void frameListClicked(const QModelIndex &index);

    // Updates the brush size to the new value.
    void brushSizeChanged(int value);

private:
    Ui::MainWindow *ui;

    SpriteFrameCollection frames;
    SpriteFrame *currentFrame;

    int animationFrameIndex;
    QTimer animationTimer;

    ToolBrush brush;
    int brushSize;
    QColor currentColor;

    QStringListModel frameModel;

    int canvasWidth;
    int canvasHeight;        

    NewSpriteDialog newDialog;
    QString currentFileName;
    bool isChanged;

    void changeSelectedColor(QColor color);
    void toolBrushAction(int x, int y);
    void updateListView(int);
    void currentButtonRemoveHighlight(ToolBrush currBrush);
    void initNewProject();
};

#endif // MAINWINDOW_H
