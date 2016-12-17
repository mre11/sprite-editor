// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include <QObject>
#include <QImage>
#include <fstream>

class SpriteFrame : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrame(int width, int height, QObject *parent = 0);

    // Darkens the point at x,y in the QImage
    void darken(int x, int y);

    // Lightens the point at x,y in the QImage
    void lighten(int x, int y);

    // Resets the point at x,y to transparent white.
    void erase(int x, int y);

    // Changes the color at x,y to the specified color.
    void changeColor(int x, int y, QColor color);

    // Collects the color at x,y and replaces all connected pixels with the same color to the replacement color
    void fillColor(int x, int y, QColor replacementColor);

    // Collects the color at x,y
    QColor eyeDrop(int x, int y);

    // Resets all pixels on the frame to the white transparent.
    void resetFrame();

    // Returns a reference to a readonly version of the qimage.
    const QImage *getImage();

    // saves the frame.
    void save(std::ofstream &outputFile);

private:
    QImage image;

    // Saves a row to the specified output stream.
    void saveRow(int rowNum, std::ofstream &outputFile);

    // Returns a boolean that states whether a click is within dimensions.
    bool outOfRange(int x, int y);
};

#endif // SPRITEFRAME_H
