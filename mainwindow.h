#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <spriteframecollection.h>

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

private:
    Ui::MainWindow *ui;
    SpriteFrameCollection frames;
    QTimer animationTimer;

    void toggleGridDisplay();
};

#endif // MAINWINDOW_H
