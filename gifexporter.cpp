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
        QImage formattedImage = frames.getFrame(i)->getImage()->convertToFormat(QImage::Format_RGB888);
        QVector<QRgb> table = formattedImage.colorTable();
//        QVector<QRgb> table = frames.getFrame(i)->getImage()->colorTable();


        int tableSize = table.size();
        uint8_t image[tableSize*3];
        for(int j = 0; j < tableSize; j++)
        {
            QRgb pixel = table.at(j);
            image[(j*3)+0] = qRed(pixel);
            image[(j*3)+1] = qGreen(pixel);
            image[(j*3)+2] = qBlue(pixel);
        }
        GifWriteFrame(gifwriter, image, frames.getWidth(), frames.getHeight(), 10);
    }
    //Finally, call GifEnd() to close the file handle and free memory.
    GifEnd(gifwriter);
}
