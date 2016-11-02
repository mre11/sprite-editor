#include "gifexporter.h"
#include "gif-h/gif.h"

void GifExporter::exportGif(QString fileName, SpriteFrameCollection &frames)
{
    // Create a GifWriter struct.
    GifWriter gifwriter;

    // Pass the struct to GifBegin() to initialize values and write the file header.
    GifBegin(&gifwriter, fileName.toStdString().c_str(), frames.getWidth(), frames.getHeight(), 10);

    // Pass frames of the animation to GifWriteFrame().
    int numbFrames = frames.count();
    for(int i = 0; i < numbFrames; i++)
    {
        //GifWriteFrame(&gifwriter, frames.getFrame(i)->getImage(), frames.getWidth(), frames.getHeight(), 10);
    }

    // Finally, call GifEnd() to close the file handle and free memory.
    GifEnd(&gifwriter);
}
