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

    ui->primaryColorButton->setStyleSheet("background-color:" + currentColor.name() + ";");
    updateCanvas();

    // Create first frame in the listview.
    frameModel = new QStringListModel(this);
    QStringList frameOne;
    frameOne << "frame1";
    frameModel->setStringList(frameOne);
    ui->listView->setModel(frameModel);

    // Create connections
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
    connect(ui->menuExport, &QMenu::triggered, this, &MainWindow::exportMenuItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::primaryColorClicked()
{
    // TODO: For some reason if you have multiple frames, this method is called multiple times.
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->primaryColorButton->setStyleSheet("background-color:" + color.name() + ";");
    currentColor = color;
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
            currentFrame->fillColor(x, y, currentColor);
            break;
        default:
            currentFrame->changeColor(x, y, currentColor);
    }
}

void MainWindow::fileMenuItemClicked()
{
    QString fileMenuItem = sender()->objectName();
    QString fileName;
    // TODO: Create QFileDialog first and apply all filters to the dialog before using.
    if(fileMenuItem == "actionOpen")
    {
        fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath());
        //frames.open(fileName.toStdString()); // Not working for some reason
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
        // TODO: Call SpriteFrameCollect Save Method.
        // TODO: Just have save_as? Or keep current location in spriteframecollection and save there.
    }
    else if(fileMenuItem == "actionSave_As")
    {
        fileName = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath());
        //frames.save(fileName.toStdString());
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

void MainWindow::exportMenuItemClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath());
    exporter.exportGif(fileName.toStdString(), frames);
}

/// Adds a new frame to the list view and the sprite frame collection.
void MainWindow::on_addFrameButton_clicked()
{
    // Add a new frame to the last row.
    int lastRow = frameModel->rowCount();

    //update ui and allow the user to edit the current frames name.
    frameModel->insertRows(lastRow, 1);
    ui->listView->setCurrentIndex(frameModel->index(lastRow));
    ui->listView->edit(frameModel->index(lastRow));

    // Add a new frame to the spriteframecollection and update the canvas.
    frames.addFrame();
    currentFrame = frames.getFrame(lastRow);
    ui->canvas->setPixmap(QPixmap::fromImage(*(currentFrame->getImage())));
    ui->canvas->setStyleSheet("border: 2px solid black");
    updateCanvas();

    // Initialize current frames connections.
    connect(ui->canvas, &SpriteCanvas::mouseClicked, this, &MainWindow::processMouseClick);
    connect(currentFrame, &SpriteFrame::frameWasUpdated, this, &MainWindow::updateCanvas);
    connect(ui->primaryColorButton, &QPushButton::clicked, this, &MainWindow::primaryColorClicked);
}

/// Resets the current frame.
void MainWindow::on_restFrameButton_clicked()
{
    currentFrame->resetFrame();
}

/// Deletes the selected item in the list view.
void MainWindow::on_deleteFrameButton_clicked()
{
    if(frames.getNumbFrames() > 1)
    {
        // Delete Sprite frame from the collection.
        frames.deleteFrame(ui->listView->currentIndex().row());

        // Delete the list view item from the model.
        frameModel->removeRows(ui->listView->currentIndex().row(), 1);

        // set the current frame to the first frame.
        currentFrame = frames.getFrame(0);

        // select the first list view item.
        ui->listView->setCurrentIndex(frameModel->index(0, 0));

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
