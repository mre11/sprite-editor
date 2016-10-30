// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QImage>
#include <QMessageBox>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      frames(30, 25, this),
      brush(ToolBrush::Brush),
      currentColor(0, 0, 0)
{
    ui->setupUi(this);

    canvasWidth = ui->canvas->width();
    canvasHeight = ui->canvas->height();

    currentFrame = frames.getFrame(0);
    ui->canvas->setPixmap(QPixmap::fromImage(*(currentFrame->getImage())));
    ui->canvas->setStyleSheet("border: 2px solid black");
    updateCanvas();

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

    //ui->widget_2->setWindowFlags(Qt::Widget);
    //ui->scrollArea->setWidget(colorSelector);

    // Create connections
    connect(ui->canvas, &SpriteCanvas::mouseClicked,
            this, &MainWindow::processMouseClick);
    connect(currentFrame, &SpriteFrame::frameWasUpdated,
            this, &MainWindow::updateCanvas);

    //QObjectList list = ui->gridLayout->findChildren<QPushButton*>();
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->lightenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->darkenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->gridButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eyeDropButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAnimation()
{

}

void MainWindow::toolBrushClicked()
{
    QString buttonName = sender()->objectName();

    if (buttonName == "brushButton")
        brush = ToolBrush::Brush;
    else if (buttonName == "lightenButton")
        brush = ToolBrush::Lighten;
    else if (buttonName == "darkenButton")
        brush = ToolBrush::Darken;
    else if (buttonName == "gridButton")
        toggleGridDisplay();
    else if (buttonName == "eyeDropButton")
        brush = ToolBrush::EyeDrop;
    else if (buttonName == "eraserButton")
        brush = ToolBrush::Eraser;
    else if (buttonName == "fillButton")
        brush = ToolBrush::Bucket;
    // TODO need bucket button and hookups
}

void MainWindow::processMouseClick(QPoint pt)
{
    int x = pt.x() * frames.getWidth() / canvasWidth;
    int y = pt.y() * frames.getHeight() / canvasHeight;

    switch (brush)
    {
        case ToolBrush::Darken:
            currentFrame->darken(x, y);
            break;
        case ToolBrush::Lighten:
            currentFrame->lighten(x, y);
            break;
        case ToolBrush::Brush:
            currentFrame->changeColor(x, y, currentColor);
            break;
        case ToolBrush::Eraser:
            currentFrame->erase(x, y);
            break;
        case ToolBrush::EyeDrop:
            currentFrame->eyeDrop(x, y);
            break;
        case ToolBrush::Bucket:
            currentFrame->fillColor(x, y, QColor(230, 212, 150));
            break;
        default:
            currentFrame->changeColor(x, y, currentColor);
    }
}

void MainWindow::updateCanvas()
{
    auto image = currentFrame->getImage();
    QImage scaledImage = image->scaled(canvasWidth, canvasHeight, Qt::KeepAspectRatio);
    ui->canvas->setPixmap(QPixmap::fromImage(scaledImage));
    ui->canvas->update();
}

void MainWindow::toggleGridDisplay()
{

}
