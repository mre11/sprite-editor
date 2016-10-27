// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QImage>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      frames(271, 281, this)
{
    ui->setupUi(this);

    currentFrame = frames.at(1); // TODO fix this (want it to be at 0, we are adding frame to qvector wrong or something
    currentColor = QColor::black;
    brush = ToolBrush::Brush;

    ui->canvas->setPixmap(QPixmap::fromImage(*(currentFrame->getImage())));

    //QListIterator h(list);
    //while(h->hasNext())
    //{
    //    QPushButton *tempbutton = h.next();
    //    connect(tempbutton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    //}

   // for(int i = 1; i <= 6; i++)
    //{
    //   QPushButton *button = ui->gridLayout->findChild<QPushButton*>("pushButton_" + i);
     //  connect(button, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    //}

    // TODO: Try to move to the group box.
    //QColorDialog *colorSelector = new QColorDialog(ui->widget);
    //colorSelector->setWindowFlags(Qt::Widget);
    //colorSelector->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    //QImage image(50, 50, QImage::Format_ARGB32);
    //image.fill(QColor(255, 0, 0, 255));

    //ui->widget_2->setWindowFlags(Qt::Widget);
    //ui->scrollArea->setWidget(colorSelector);

    connect(ui->canvas, &SpriteCanvas::mouseClicked,
            this, &MainWindow::processMouseClick);
    connect(currentFrame, &SpriteFrame::frameWasUpdated,
            this, &MainWindow::updateCanvas);

    //QObjectList list = ui->gridLayout->findChildren<QPushButton*>();
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
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

void MainWindow::toolBrushClicked()
{
    QObject *s = sender();
    QString y = s->objectName();

    QMessageBox h;
    h.setText(y);
    h.exec();
    h.show();
}

void MainWindow::processMouseClick(QPoint pt)
{
    currentFrame->changeColor(pt.x(), pt.y(), currentColor);
}

void MainWindow::updateCanvas()
{
    auto image = currentFrame->getImage();
    image->scaled(271, 281, Qt::KeepAspectRatio);
    ui->canvas->setPixmap(QPixmap::fromImage(*image));
    ui->canvas->update();
}
