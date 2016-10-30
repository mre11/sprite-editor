// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframe.h"
#include <QQueue>

using namespace std;

SpriteFrame::SpriteFrame(int width, int height, QObject *parent)
    : QObject(parent), image(width, height, QImage::Format_ARGB32)
{
    image.fill(QColor(0, 0, 0, 0));
}

void SpriteFrame::darken(int x, int y)
{
    if (outOfRange(x, y)) return;

    auto color = image.pixelColor(x, y);
    modifyAlpha(25, color);
    changeColor(x, y, color);
}

void SpriteFrame::lighten(int x, int y)
{
    if (outOfRange(x, y)) return;

    auto color = image.pixelColor(x, y);
    modifyAlpha(-25, color);
    changeColor(x, y, color);
}

void SpriteFrame::erase(int x, int y)
{
    changeColor(x, y, QColor(0,0,0,0));

}

void SpriteFrame::changeColor(int x, int y, QColor color)
{
    if (outOfRange(x, y)) return;

    image.setPixelColor(x, y, color);
    emit frameWasUpdated(&image);
}

void SpriteFrame::fillColor(int x, int y, QColor replacementColor)
{
    QPoint first(x, y);
    QColor targetColor = this->image.pixelColor(first);

    //if (outOfRange(x, y)) return;
    if(targetColor == replacementColor)
        return;

    //if(firstColor != targetColor)
     //   return;

    QQueue<QPoint> *queue = new QQueue<QPoint>();

    queue->enqueue(first);

    while(!queue->isEmpty())
    {
        QPoint n = queue->dequeue();
        QColor nColor = this->image.pixelColor(n);

        this->image.setPixelColor(n, replacementColor);

        // West
        QPoint west(n.x() - 1, n.y());
        if((west.x() > 0 && west.x() < this->image.width()) && this->image.pixelColor(n.x() - 1, n.y()) == targetColor)
        {
            queue->enqueue(west);
        }

        // East
        QPoint east(n.x() + 1, n.y());
        if(east.x() >0 && east.x() < this->image.width() && this->image.pixelColor(n.x() + 1, n.y()) == targetColor)
        {
            queue->enqueue(east);
        }

        // North
        QPoint north(n.x(), n.y() - 1);
        if(north.y() > 0  && north.y() < this->image.height() && this->image.pixelColor(n.x(), n.y() - 1) == targetColor)
        {
            queue->enqueue(north);
        }

        // South
        QPoint south(n.x(), n.y() + 1);
        if(south.y() > 0 && south.y() < this->image.height() &&  this->image.pixelColor(n.x(), n.y() + 1) == targetColor)
        {
            queue->enqueue(south);
        }

    }




}

QColor SpriteFrame::eyeDrop(int x, int y)
{
    return image.pixelColor(x, y);
}

const QImage *SpriteFrame::getImage()
{
    return &image;
}

void SpriteFrame::save(ofstream &outputFile)
{
    for (int i = 0; i < image.height(); i++)
    {
        saveRow(i, outputFile);
    }
}

void SpriteFrame::modifyAlpha(int amount, QColor &color)
{
    int currentAlpha = color.alpha();
    int newAlpha = currentAlpha + amount;

    if (newAlpha < 0)
        newAlpha = 0;
    else if (newAlpha > 255)
        newAlpha = 255;

    color.setAlpha(newAlpha);
}

void SpriteFrame::saveRow(int rowNum, ofstream &outputFile)
{
    // loop across the row, writing each pixel to the file
    for (int i = 0; i < image.width(); i++)
    {
        QColor pixel = image.pixelColor(i, rowNum);
        outputFile << pixel.red() << " " << pixel.green() << " " << pixel.blue() << " " << pixel.alpha() << " ";
    }
    outputFile << '\n'; // end the row with a newline
}

bool SpriteFrame::outOfRange(int x, int y)
{
    return x < 0 || y < 0 || x >= image.width() || y >= image.height();
}
