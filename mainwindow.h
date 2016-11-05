// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
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
    void setAnimationTimerInterval(int fps);
    void toolBrushClicked();
    void processMouseClick(QPoint pt);
    void updateCanvas();
    void toggleGridDisplay();
    void primaryColorClicked();

    // menu items
    void fileMenuItemClicked();
    void exportMenuItemClicked();

private slots:
    void addFrameClicked();
    void resetFrameClicked();
    void deleteFrameClicked();
    void frameListClicked(const QModelIndex &index);
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

    QString currentFileName;
    bool isChanged;

    void changeSelectedColor(QColor color);
    void toolBrushAction(int x, int y);
    void updateListView(int);
    NewSpriteDialog newDialog;
};

#endif // MAINWINDOW_H
