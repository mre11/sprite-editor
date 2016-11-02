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
    changeColor(x, y, color.darker(110));
}

void SpriteFrame::lighten(int x, int y)
{
    if (outOfRange(x, y)) return;

    auto color = image.pixelColor(x, y);
    changeColor(x, y, color.lighter(110));
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
    QColor targetColor = image.pixelColor(first);

    if(targetColor == replacementColor)
        return;

    QQueue<QPoint> *queue = new QQueue<QPoint>();

    queue->enqueue(first);

    while(!queue->isEmpty())
    {

        QPoint n = queue->dequeue();
        QColor nColor = this->image.pixelColor(n);

        if(nColor != targetColor)
            continue;

        image.setPixelColor(n, replacementColor);

        QPoint west(n.x() - 1, n.y());
        QPoint east(n.x() + 1, n.y());
        QPoint north(n.x(), n.y() - 1);
        QPoint south(n.x(), n.y() + 1);

        // Grab qpoint west if it is the same as the target color.
        if(west.x() >= 0 && west.x() < image.width() && image.pixelColor(west) == targetColor)
            queue->enqueue(west);

        // Grab qpoint east if it is the same as the target color.
        if(east.x() >= 0 && east.x() < image.width() && image.pixelColor(east) == targetColor)
            queue->enqueue(east);

        // Grab qpoint north if it is the same as the target color.
        if(north.y() >= 0  && north.y() < image.height() && image.pixelColor(north) == targetColor)
            queue->enqueue(north);

        // Grab qpoint south if it is the same as the target color.
        if(south.y() >= 0 && south.y() < image.height() &&  image.pixelColor(south) == targetColor)
            queue->enqueue(south);
    }

    emit frameWasUpdated(&image);
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

void SpriteFrame::resetFrame()
{
    image.fill(QColor(0, 0, 0, 0));
    emit frameWasUpdated(&image);
}
