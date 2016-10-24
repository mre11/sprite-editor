// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef SPRITEFRAMECOLLECTION_H
#define SPRITEFRAMECOLLECTION_H

#include <QObject>
#include <QVector>
#include <memory>
#include "spriteframe.h"

class SpriteFrameCollection : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrameCollection(int width, int height, QObject *parent = 0);
    ~SpriteFrameCollection();

    void addFrame();
    void deleteFrame(int index);
    void load();
    void save();

signals:

public slots:
private:
    int frameHeight;
    int frameWidth;
    QVector<SpriteFrame *> frames;
};

#endif // SPRITEFRAMECOLLECTION_H
