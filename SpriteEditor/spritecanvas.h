// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
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

    // Toggles grid display on and off
    void toggleGridDisplay();

    // Returns a boolean stating whether the grid display is on or off.
    bool isGridOn();

    // Sets the sprite height
    void setSpriteHeight(int height);

    // Sets the sprite width
    void setSpriteWidth(int width);

signals:

    // Handles the mouse click event at the specified QPoint
    void mouseClicked(QPoint pt);

protected:
    // Paints the current canvas
    virtual void paintEvent(QPaintEvent *event) override;

    // Emits a signal when the mouse is pressed.
    virtual void mousePressEvent(QMouseEvent *event);

    // Takes the current point and emits the mousepress event.
    virtual void mouseMoveEvent(QMouseEvent *event);

    bool gridOn;
    int spriteHeight;
    int spriteWidth;
};

#endif // SPRITECANVAS_H
