#ifndef GIFEXPORTER_H
#define GIFEXPORTER_H

#include <string>
#include "spriteframecollection.h"

class GifExporter
{
public:
    void exportGif(std::string fileName, SpriteFrameCollection &frames);
};

#endif // GIFEXPORTER_H
