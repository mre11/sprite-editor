// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spritecanvas.h"
#include <QPainter>

SpriteCanvas::SpriteCanvas(QWidget *parent)
    : QLabel(parent), gridOn(false)
{
}

void SpriteCanvas::toggleGridDisplay()
{
    gridOn = !gridOn;
}

void SpriteCanvas::setSpriteHeight(int height)
{
    spriteHeight = height;
}

void SpriteCanvas::setSpriteWidth(int width)
{
    spriteWidth = width;
}

void SpriteCanvas::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    if (gridOn)
    {
        int horizLineSpacing = height() / spriteHeight;
        int vertLineSpacing = width() / spriteWidth;

        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 1));

        int x = vertLineSpacing;
        int y = horizLineSpacing;

        while (x < width())
        {
            painter.drawLine(x, 0, x, height());
            x += vertLineSpacing;
        }
        while (y < height())
        {
            painter.drawLine(0, y, width(), y);
            y += horizLineSpacing;
        }
    }
}

void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event->pos());
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    mousePressEvent(event);
}
