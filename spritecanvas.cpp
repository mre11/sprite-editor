// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spritecanvas.h"
#include <QMessageBox>

SpriteCanvas::SpriteCanvas(QWidget *parent)
    : QLabel(parent)
{

}

void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event->pos());
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    mousePressEvent(event);
}
