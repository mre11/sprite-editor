// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newspritedialog.h"

#include <QColorDialog>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QStringListModel>

#include "gifexporter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      frames(20, 20, this),
      brush(ToolBrush::Brush),
      currentColor(0, 0, 0),
      frameModel(this),
      currentFileName(""),
      animationTimer(this),
      animationFrameIndex(0),
      brushSize(1),
      isChanged(false),
      newDialog(this)
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: rgb(150, 150, 150) }"
                        "QPushButton { color: white; background-color: rgb(63, 63, 63) }"
                        "QGroupBox { border: 1px solid black; font-size: 12px }"
                        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 3px; }"
                        "SpriteCanvas { background-color: lightgray; border: 1px solid black }");

    currentFrame = frames.getFrame(0);

    // Set up canvas
    canvasWidth = ui->canvas->width();
    canvasHeight = ui->canvas->height();
    updateCanvas();

    ui->primaryColorButton->setStyleSheet("background-color:" + currentColor.name() + ";");
    ui->frameListView->setModel(&frameModel);
    updateListView(0);

    ui->animationFpsDisplayLabel->setNum(ui->animationFpsSlider->value());
    ui->animationDisplay->setPixmap(QPixmap::fromImage(*(currentFrame->getImage())));
    setAnimationTimerInterval(ui->animationFpsSlider->value());
    animationTimer.start();

    ui->brushButton->setStyleSheet("background-color:green"); // brush is active to start

    initNewProject();

    connect(ui->canvas, &SpriteCanvas::mouseClicked, this, &MainWindow::processMouseClick);
    connect(ui->primaryColorButton, &QPushButton::clicked, this, &MainWindow::primaryColorClicked);

    // Tools connections
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->lightenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->darkenButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->gridButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eyeDropButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &MainWindow::toolBrushClicked);
    connect(ui->brushSizeBox, SIGNAL(valueChanged(int)), this, SLOT(brushSizeChanged(int)));

    // Animation display connections
    connect(ui->animationFpsSlider, SIGNAL(valueChanged(int)), ui->animationFpsDisplayLabel, SLOT(setNum(int)));
    connect(ui->animationFpsSlider, &QSlider::valueChanged, this, &MainWindow::setAnimationTimerInterval);
    connect(&animationTimer, &QTimer::timeout, this, &MainWindow::updateAnimation);

    // Frames list connections
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::addFrameClicked);
    connect(ui->resetFrameButton, &QPushButton::clicked, this, &MainWindow::resetFrameClicked);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &MainWindow::deleteFrameClicked);
    connect(ui->frameListView, &QListView::clicked, this, &MainWindow::frameListClicked);

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
    changeSelectedColor(color);
}

void MainWindow::updateAnimation()
{
    if (frames.count() > 1)
    {
        if (++animationFrameIndex >= frames.count())
            animationFrameIndex = 0;

        SpriteFrame *frame = frames.getFrame(animationFrameIndex);
        const QImage *actualImage = frame->getImage();
        if (ui->animationScaledButton->isChecked())
        {
            int scaledWidth = ui->animationDisplay->width();
            int scaledHeight = ui->animationDisplay->height();
            QImage scaledImage = actualImage->scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio);
            ui->animationDisplay->setPixmap(QPixmap::fromImage(scaledImage));
        }
        else
        {
            ui->animationDisplay->setPixmap(QPixmap::fromImage(*actualImage));
        }

        ui->animationDisplay->update();
    }
}

void MainWindow::setAnimationTimerInterval(int fps)
{
    animationTimer.setInterval(1000 / fps); // convert fps to milliseconds
}

/// Handles updating the current sprite tool.
void MainWindow::toolBrushClicked()
{
    ToolBrush oldBrush = brush;
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

    if (buttonName != "gridButton")
    {
        currentButtonRemoveHighlight(oldBrush);
        QPushButton *tempButton = static_cast<QPushButton *>(sender());
        tempButton->setStyleSheet("background-color:green");
    }
}


/// Applys the current brush tool to the x,y location that was clicked.
void MainWindow::processMouseClick(QPoint pt)
{
    int x = pt.x() * frames.getWidth() / canvasWidth;
    int y = pt.y() * frames.getHeight() / canvasHeight;

    if (brush == ToolBrush::EyeDrop)
        changeSelectedColor(currentFrame->eyeDrop(x, y));

    else if (brush == ToolBrush::Bucket)
        currentFrame->fillColor(x, y, currentColor);
    else
    {
        switch (brushSize)
        {
            case 4:
                toolBrushAction(x + 2, y - 1);
                toolBrushAction(x + 2, y);
                toolBrushAction(x + 2, y + 1);
                toolBrushAction(x + 2, y + 2);
                toolBrushAction(x + 1, y + 2);
                toolBrushAction(x, y + 2);
                toolBrushAction(x - 1, y + 2);
            case 3:
                toolBrushAction(x - 1, y + 1);
                toolBrushAction(x - 1, y);
                toolBrushAction(x - 1, y - 1);
                toolBrushAction(x, y - 1);
                toolBrushAction(x + 1, y - 1);
            case 2:
                toolBrushAction(x + 1, y);
                toolBrushAction(x + 1, y + 1);
                toolBrushAction(x, y + 1);
            default:
                toolBrushAction(x, y);
        }
    }
    updateCanvas();
}

/// Handles the filemenuitem events.
void MainWindow::fileMenuItemClicked()
{
    QString fileMenuItem = sender()->objectName();

    if (fileMenuItem == "actionOpen") // TODO size isn't updated properly somewhere... open smaller sprite when you have bigger sprite active
    {
        if (isChanged)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Overwrite", "You have unsaved changes! Would you like to continue without saving?", QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath());

                if (fileName != NULL)
                {
                    frames.open(fileName);

                    //frameModel.removeRows(0, frameModel.rowCount());

                    // Update the current frame.
                    currentFrame = frames.getFrame(0);

                    // set the file name.
                    currentFileName = fileName;
                    for(int i = 1; i < frames.count(); i++)
                    {
                        updateListView(i);
                    }
                    updateCanvas();
                }
            }
        }
        else
        {
            QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath());

            if (fileName != NULL)
            {
                frames.open(fileName);

                // Update the current frame.
                currentFrame = frames.getFrame(0);
                frameModel.removeRows(0, frameModel.rowCount());
                // set the file name.
                currentFileName = fileName;
                for(int i = 1; i < frames.count(); i++)
                {
                    updateListView(i);
                }
                updateCanvas();
            }
        }
    }
    else if (fileMenuItem == "actionNew")
    {

        if (isChanged)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Overwrite", "You have unsaved changes! Would you like to continue without saving?", QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                initNewProject();
            }
        }
        else
        {
            initNewProject();
        }
    }
    else if (fileMenuItem == "actionSave_As" || fileMenuItem == "actionSave")
    {
        if (currentFileName.isEmpty() || fileMenuItem == "actionSave_As")
        {
            currentFileName = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath(), "Sprite Sheet Project (*.ssp)");
        }
        if (!currentFileName.isEmpty())
        {
            frames.save(currentFileName);
            isChanged = false;
        }
    }
    else if (fileMenuItem == "actionExit")
    {
        QMessageBox::StandardButton response;
        response = QMessageBox::question(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No);

        if (response == QMessageBox::Yes)
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
    ui->canvas->isGridOn() ? ui->gridButton->setStyleSheet("") : ui->gridButton->setStyleSheet("background-color: green");
    ui->canvas->toggleGridDisplay();
    ui->canvas->update();
}

void MainWindow::exportMenuItemClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export", QDir::homePath(), "Image (*.gif)");
    GifExporter exporter;
    exporter.exportGif(fileName, frames);
}

/// Updates the list view with new rows that are named according to their frame index.
void MainWindow::updateListView(int frameNumber)
{
    QStringList frames = frameModel.stringList();
    QString t = "frame" + QString::number(frameNumber);
    frames.append(t);
    frameModel.setStringList(frames);
}

/// Adds a new frame to the list view and the sprite frame collection.
void MainWindow::addFrameClicked()
{
    // Get the last rows index.
    int lastRow = frameModel.rowCount();

    // Add a new frame to the spriteframecollection and update the canvas.
    frames.addFrame();
    currentFrame = frames.getFrame(lastRow);
    updateListView(lastRow);
    updateCanvas();
}

/// Resets the current frame.
void MainWindow::resetFrameClicked()
{
    currentFrame->resetFrame();
    updateCanvas();
}

/// Deletes the selected item in the list view.
void MainWindow::deleteFrameClicked()
{
    if (frames.count() > 1 && ui->frameListView->currentIndex().row() > -1)
    {
        // Delete Sprite frame from the collection.
        frames.deleteFrame(ui->frameListView->currentIndex().row());

        // Delete the list view item from the model.
        frameModel.removeRows(ui->frameListView->currentIndex().row(), 1);

        // set the current frame to the first frame.
        currentFrame = frames.getFrame(0);

        // select the first list view item.
        ui->frameListView->setCurrentIndex(frameModel.index(0, 0));

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
void MainWindow::frameListClicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    currentFrame = frames.getFrame(selectedRow);
    updateCanvas();
}

void MainWindow::brushSizeChanged(int value)
{
    brushSize = value;
}

void MainWindow::changeSelectedColor(QColor color)
{
    // Update the button color to the selected color.
    ui->primaryColorButton->setStyleSheet("background-color:" + color.name() + ";");

    // Set the current color to the new color.
    currentColor = color;
}

void MainWindow::toolBrushAction(int x, int y)
{
    isChanged = true;
    switch (brush)
    {
        case ToolBrush::Darken:
            currentFrame->darken(x, y);
            return;
        case ToolBrush::Lighten:
            currentFrame->lighten(x, y);
            return;
        case ToolBrush::Brush:
            currentFrame->changeColor(x, y, currentColor);
            return;
        case ToolBrush::Eraser:
            currentFrame->erase(x, y);
            return;
    }
}

void MainWindow::currentButtonRemoveHighlight(ToolBrush currBrush)
{
    QString styleSheet = "";
    switch (currBrush)
    {
        case ToolBrush::Darken:
            ui->darkenButton->setStyleSheet(styleSheet);
            break;
        case ToolBrush::Lighten:
            ui->lightenButton->setStyleSheet(styleSheet);
            break;
        case ToolBrush::Brush:
            ui->brushButton->setStyleSheet(styleSheet);
            break;
        case ToolBrush::Eraser:
            ui->eraserButton->setStyleSheet(styleSheet);
            break;
        case ToolBrush::Bucket:
            ui->fillButton->setStyleSheet(styleSheet);
            break;
        case ToolBrush::EyeDrop:
            ui->eyeDropButton->setStyleSheet(styleSheet);
            break;
    }
}

/// Asks the user for height and width and sets up a new project
void MainWindow::initNewProject()
{
    frameModel.removeRows(0, frameModel.rowCount());
    updateListView(0);
    newDialog.exec();
    int width, height;
    newDialog.GetResults(width, height);
    frames.changeFrameSize(width, height);
    currentFrame = frames.getFrame(0);
    updateCanvas();
}
