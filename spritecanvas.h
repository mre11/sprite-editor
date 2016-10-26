// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QLabel>

class SpriteCanvas : public QLabel
{
    Q_OBJECT

public:
    explicit SpriteCanvas(QWidget *parent = 0);

protected slots:
    //virtual void paintEvent(QPaintEvent *) override;
    //virtual void mousePressEvent(QMouseEvent *ev) override;
};

#endif // SPRITECANVAS_H
