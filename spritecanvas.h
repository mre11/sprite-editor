// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QLabel>
#include <QMouseEvent>

class SpriteCanvas : public QLabel
{
    Q_OBJECT

public:
    explicit SpriteCanvas(QWidget *parent = 0);

signals:
    void mouseClicked(QPoint pt);


protected:
    //virtual void paintEvent(QPaintEvent *) override;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // SPRITECANVAS_H
