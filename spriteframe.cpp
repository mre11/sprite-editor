// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframe.h"

SpriteFrame::SpriteFrame(int width, int height, QObject *parent)
    : QObject(parent), image(width, height, QImage::Format_ARGB32)
{
    image.fill(QColor(0, 0, 0, 0));
}

void SpriteFrame::darken(int x, int y)
{

}

void SpriteFrame::erase(int x, int y)
{

}

void SpriteFrame::changeColor(int x, int y, QRgb color)
{

}

void SpriteFrame::fillColor(int x, int y, QRgb replacementColor)
{

}

void SpriteFrame::lighten(int x, int y)
{

}

const QImage *SpriteFrame::getImage()
{
    return &image;
}
