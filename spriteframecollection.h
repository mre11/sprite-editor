// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
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

    void addFrame();
    void deleteFrame(int index);
    int getWidth();
    int getHeight();
    void load();
    void open(std::string filePath);
    void save(std::string filePath);
    SpriteFrame *getFrame(int index);
    int getNumbFrames();

signals:

public slots:
private:
    int frameHeight;
    int frameWidth;

    QVector<QSharedPointer<SpriteFrame>> frames;
};

#endif // SPRITEFRAMECOLLECTION_H
