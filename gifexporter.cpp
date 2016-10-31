#include "gifexporter.h"
#include "gif-h/gif.h"

void GifExporter::exportGif(std::string fileName, SpriteFrameCollection &frames)
{
    // From readme.md:
    //Usage:
    //-------------------
    //Create a GifWriter struct.
    GifWriter* gifwriter;
    //Pass the struct to GifBegin() to initialize values and write the file header.
    GifBegin(gifwriter, fileName.c_str(), frames.getWidth(), frames.getHeight(), 10);
    //Pass frames of the animation to GifWriteFrame().
    int numbFrames = frames.getNumbFrames();
    for(int i = 0; i < numbFrames; i++)
    {
        //GifWriteFrame(gifwriter, frames.getFrame(i)->getImage(), frames.getWidth(), frames.getHeight(), 10);
    }
    //Finally, call GifEnd() to close the file handle and free memory.
    GifEnd(gifwriter);
}
