// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef GIFEXPORTER_H
#define GIFEXPORTER_H

#include <QString>
#include "spriteframecollection.h"

class GifExporter
{
public:
    void exportGif(QString fileName, SpriteFrameCollection &frames);
};

#endif // GIFEXPORTER_H
