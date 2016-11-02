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
