// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      frames(20, 20, this),
      brush(ToolBrush::Brush),
      currentColor(0, 0, 0),
      frameModel(this),
      currentFileName("")
{
    ui->setupUi(this);

    currentFrame = frames.getFrame(0);

    // Set up canvas
    canvasWidth = ui->canvas->width();
    canvasHeight = ui->canvas->height();
    updateCanvas();

    ui->primaryColorButton->setStyleSheet("background-color:" + currentColor.name() + ";");    

    // Create first frame in the listview.
    QStringList stringList;
    stringList << "frame1";
    frameModel.setStringList(stringList);
    ui->listView->setModel(&frameModel);

    connect(ui->canvas, &SpriteCanvas::mouseClicked, this, &MainWindow::processMouseClick);
    connect(currentFrame, &SpriteFrame::frameWasUpdated, this, &MainWindow::updateCanvas);
    connect(ui->primaryColorButton, &QPushButton::clicked, this, &MainWindow::primaryColorClicked);

    // Connect brush tools.
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->lightenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->darkenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->gridButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eyeDropButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);

    // File Menu Item connections
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::fileMenuItemClicked);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::fileMenuItemClicked);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::fileMenuItemClicked);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::fileMenuItemClicked);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::fileMenuItemClicked);

    // Export Menu Item Connections
    connect(ui->actionExport_GIF, &QAction::triggered, this, &MainWindow::exportMenuItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// Changes the current color being used.
void MainWindow::primaryColorClicked()
{
    // Open the QColorDialog and display the current color.
    QColor color = QColorDialog::getColor(currentColor, this);

    // Update the button color to the selected color.
    ui->primaryColorButton->setStyleSheet("background-color:" + color.name() + ";");

    // Set the current color to the new color.
    currentColor = color;
}

void MainWindow::updateAnimation()
{

}

/// Handles updating the current sprite tool.
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
// Optional:
//    QPushButton *tempButton = (QPushButton*)sender();
//    tempButton->setStyleSheet("background-color:yellow");
}


/// Applys the current brush tool to the x,y location that was clicked.
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
            currentFrame->fillColor(x, y, currentColor);
            break;
        default:
            currentFrame->changeColor(x, y, currentColor);
    }
}

/// Handles the filemenuitem events.
void MainWindow::fileMenuItemClicked()
{
    QString fileMenuItem = sender()->objectName();

    // TODO: Create QFileDialog first and apply all filters to the dialog before using.
    if(fileMenuItem == "actionOpen")
    {
        currentFileName = QFileDialog::getOpenFileName(this, "Open", QDir::homePath(), "Sprite Sheet Project (*.ssp)");
        frames.open(currentFileName);
    }
    else if(fileMenuItem == "actionNew")
    {
//        QDialog newDialog(this);
//        QFormLayout newForm(&newDialog);

//        QLineEdit *w = new QLineEdit(&newDialog);
//        inputDialog->ad
//        inputDialog->setOptions(QInputDialog::NoButtons);
//        bool ok;
//        QString wh = inputDialog->getText(NULL, "New Canvas", "Width", QLineEdit::Normal, QDir::home().dirName(), &ok);
        // TODO: Make New Dialog Form.
    }
    else if(fileMenuItem == "actionSave")
    {
        // TODO get rid of code duplication between save and save as
        if (currentFileName.isEmpty())
        {
            currentFileName = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath(), "Sprite Sheet Project (*.ssp)");
        }

        frames.save(currentFileName);
    }
    else if(fileMenuItem == "actionSave_As")
    {
        currentFileName = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath(), "Sprite Sheet Project (*.ssp)");
        frames.save(currentFileName);
    }
    else if(fileMenuItem == "actionExit")
    {
        // TODO: Ask if anything needs to be saved.
        QMessageBox::StandardButton response;
        response = QMessageBox::question(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No);

        if(response == QMessageBox::Yes)
        {
            close();
        }
    }
}

/// Updates the canvas to display the new scaled image.
void MainWindow::updateCanvas()
{
    auto image = currentFrame->getImage();
    QImage scaledImage = image->scaled(canvasWidth, canvasHeight, Qt::KeepAspectRatio);
    ui->canvas->setPixmap(QPixmap::fromImage(scaledImage));
    ui->canvas->setSpriteHeight(image->height());
    ui->canvas->setSpriteWidth(image->width());
    ui->canvas->update();
}

void MainWindow::toggleGridDisplay()
{
    ui->canvas->toggleGridDisplay();
    ui->canvas->update();
}

void MainWindow::exportMenuItemClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export", QDir::homePath(), "Image (*.gif)");
    GifExporter exporter;
    exporter.exportGif(fileName, frames);
}

/// Adds a new frame to the list view and the sprite frame collection.
void MainWindow::on_addFrameButton_clicked()
{
    // Add a new frame to the last row.
    int lastRow = frameModel.rowCount();

    //update ui and allow the user to edit the current frames name.
    frameModel.insertRows(lastRow, 1);
    ui->listView->setCurrentIndex(frameModel.index(lastRow));
    ui->listView->edit(frameModel.index(lastRow));

    // Add a new frame to the spriteframecollection and update the canvas.
    frames.addFrame();
    currentFrame = frames.getFrame(lastRow);
    updateCanvas();

    // Initialize current frames connections.
    connect(currentFrame, &SpriteFrame::frameWasUpdated, this, &MainWindow::updateCanvas);
}

/// Resets the current frame.
void MainWindow::on_restFrameButton_clicked()
{
    currentFrame->resetFrame();
}

/// Deletes the selected item in the list view.
void MainWindow::on_deleteFrameButton_clicked()
{
    if(frames.count() > 1)
    {
        // Delete Sprite frame from the collection.
        frames.deleteFrame(ui->listView->currentIndex().row());

        // Delete the list view item from the model.
        frameModel.removeRows(ui->listView->currentIndex().row(), 1);

        // set the current frame to the first frame.
        currentFrame = frames.getFrame(0);

        // select the first list view item.
        ui->listView->setCurrentIndex(frameModel.index(0, 0));

        // update the canvas to the new current frame.
        updateCanvas();
    }
    else
    {
        QMessageBox message;
        message.setText("Cannot delete last frame!");
        message.exec();
    }
}

/// Method is called when the selection on the list view changes.
/// Updates the canvas to the current frame.
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    currentFrame = frames.getFrame(selectedRow);
    updateCanvas();
}
