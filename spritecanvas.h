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

    void toggleGridDisplay();
    void setSpriteHeight(int height);
    void setSpriteWidth(int width);

signals:
    void mouseClicked(QPoint pt);


protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    bool gridOn;
    int spriteHeight;
    int spriteWidth;
};

#endif // SPRITECANVAS_H
