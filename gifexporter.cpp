#include "gifexporter.h"
#include "gif-h/gif.h"

void GifExporter::exportGif(std::string fileName, SpriteFrameCollection &frames)
{
    // From readme.md:
    //Usage:
    //-------------------
    //Create a GifWriter struct.

    //Pass the struct to GifBegin() to initialize values and write the file header.

    //Pass frames of the animation to GifWriteFrame().

    //Finally, call GifEnd() to close the file handle and free memory.
}
