// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
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

    void darken(int x, int y, int brushSize);
    void lighten(int x, int y, int brushSize);
    void erase(int x, int y, int brushSize);
    void changeColor(int x, int y, QColor color, int brushSize = 1);
    void fillColor(int x, int y, QColor replacementColor);
    void resetFrame();
    QColor eyeDrop(int x, int y);

    const QImage *getImage();

    void save(std::ofstream &outputFile);

signals:
    void frameWasUpdated(const QImage *image);

public slots:
private:
    QImage image;

    void saveRow(int rowNum, std::ofstream &outputFile);
    bool outOfRange(int x, int y);
    void setPixelColor(int x, int y, QColor color);
};

#endif // SPRITEFRAME_H
