// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
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

bool SpriteCanvas::isGridOn()
{
    return gridOn;
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
    // draw background pattern
    QPainter painter(this);
    QRect rect(event->rect());
    painter.setBrush(QBrush(Qt::gray, Qt::Dense7Pattern));
    painter.drawRect(rect);

    // draw the actual sprite
    QLabel::paintEvent(event);

    // draw grid on top
    if (gridOn)
    {
        int horizLineSpacing = height() / spriteHeight;
        int vertLineSpacing = width() / spriteWidth;

        QPainter gridPainter(this);
        gridPainter.setPen(QPen(Qt::black, 1));

        int x = vertLineSpacing;
        int y = horizLineSpacing;

        while (x < width())
        {
            gridPainter.drawLine(x, 0, x, height());
            x += vertLineSpacing;
        }
        while (y < height())
        {
            gridPainter.drawLine(0, y, width(), y);
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
