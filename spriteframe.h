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

    void darken(int x, int y);
    void lighten(int x, int y);
    void erase(int x, int y);
    void changeColor(int x, int y, QColor color);
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

    void modifyAlpha(int amount, QColor &color);
    void saveRow(int rowNum, std::ofstream &outputFile);
    bool outOfRange(int x, int y);
};

#endif // SPRITEFRAME_H
