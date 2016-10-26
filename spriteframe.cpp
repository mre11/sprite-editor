// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframe.h"

using namespace std;

SpriteFrame::SpriteFrame(int width, int height, QObject *parent)
    : QObject(parent), image(width, height, QImage::Format_ARGB32)
{
    image.fill(QColor(0, 0, 0, 0));
}

void SpriteFrame::darken(int x, int y)
{
    auto color = image.pixelColor(x, y);
    modifyAlpha(25, color);
    changeColor(x, y, color);
}

void SpriteFrame::lighten(int x, int y)
{
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
    image.setPixelColor(x, y, color);
}

void SpriteFrame::fillColor(int x, int y, QColor replacementColor)
{

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
