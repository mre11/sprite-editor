// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO: Try to move to the group box.
    QColorDialog *colorSelector = new QColorDialog(ui->widget);
    colorSelector->setWindowFlags(Qt::Widget);
    colorSelector->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    QImage image(50, 50, QImage::Format_ARGB32);
    image.fill(QColor(255, 0, 0, 255));

    ui->widget_2->setWindowFlags(Qt::Widget);
    ui->scrollArea->setWidget(colorSelector);

    ui->canvas->setPixmap(QPixmap::fromImage(image));
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
