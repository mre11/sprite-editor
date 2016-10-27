// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      frames(271, 281, this)
{
    ui->setupUi(this);

    // TODO: Try to move to the group box.
    //QColorDialog *colorSelector = new QColorDialog(ui->widget);
    //colorSelector->setWindowFlags(Qt::Widget);
    //colorSelector->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    //QImage image(50, 50, QImage::Format_ARGB32);
    //image.fill(QColor(255, 0, 0, 255));

    //ui->widget_2->setWindowFlags(Qt::Widget);
    //ui->scrollArea->setWidget(colorSelector);

    currentFrame = frames.at(1);

    ui->canvas->setPixmap(QPixmap::fromImage(*(currentFrame->getImage())));

    connect(ui->canvas, &SpriteCanvas::mouseClicked,
            this, &MainWindow::processMouseClick);
    connect(currentFrame, &SpriteFrame::frameWasUpdated,
            this, &MainWindow::updateCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAnimation()
{

}

void MainWindow::toggleGridDisplay()
{

}

void MainWindow::processMouseClick(QPoint pt)
{
    auto color = QColor(0, 0, 0, 255);
    currentFrame->changeColor(pt.x(), pt.y(), color);
}

void MainWindow::updateCanvas()
{
    auto image = currentFrame->getImage();
    image->scaled(271, 281, Qt::KeepAspectRatio);
    ui->canvas->setPixmap(QPixmap::fromImage(*image));
    ui->canvas->update();
}
