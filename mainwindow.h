// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "spriteframecollection.h"
#include "gifexporter.h"
#include <QStringListModel>

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

    void exportMenuItemClicked();

private slots:
    void on_addFrameButton_clicked();

    void on_restFrameButton_clicked();

    void on_deleteFrameButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    SpriteFrameCollection frames;
    QTimer animationTimer;
    SpriteFrame *currentFrame;
    ToolBrush brush;
    QColor currentColor;
    GifExporter exporter;
    QStringListModel *frameModel;

    int canvasWidth;
    int canvasHeight;
};

#endif // MAINWINDOW_H
