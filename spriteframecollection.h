// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef SPRITEFRAMECOLLECTION_H
#define SPRITEFRAMECOLLECTION_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QSharedPointer>
#include "spriteframe.h"

class SpriteFrameCollection : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrameCollection(int width, int height, QObject *parent = 0);

    // Adds a frame to the sprite frame collection.
    void addFrame();

    // Deletes the frame at index.
    void deleteFrame(int index);

    // returns the width of the sprite frames
    int getWidth();

    // returns the height of the sprite frames
    int getHeight();

    // Opens a .ssp file at the specified file path
    void open(QString filePath);

    // Saves the .ssp file to the specified file path
    void save(QString filePath);

    // returns a reference to the frame at index
    SpriteFrame *getFrame(int index);

    // returns the count of frames
    int count();

    // changes the frame size
    void changeFrameSize(int width, int height);

signals:
public slots:
private:
    int frameHeight;
    int frameWidth;

    QVector<QSharedPointer<SpriteFrame>> frames;
};

#endif // SPRITEFRAMECOLLECTION_H
