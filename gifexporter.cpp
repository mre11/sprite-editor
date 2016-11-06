// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "gifexporter.h"
#include "gif-h/gif.h"

void GifExporter::exportGif(QString fileName, SpriteFrameCollection &frames)
{
    GifWriter *gifwriter; // gif.h wants this uninitialized

    GifBegin(gifwriter, fileName.toStdString().c_str(), frames.getWidth(), frames.getHeight(), 10);

    // Pass frames of the animation to GifWriteFrame().
    for(int i = 0; i < frames.count(); i++)
    {
        QImage iFrame = *(frames.getFrame(i)->getImage());
        int frameWidth = iFrame.width();
        int frameHeight = iFrame.height();
        int numbPixels = frameWidth * frameHeight;

        uint8_t *image = new uint8_t[numbPixels*4];
        int imageIndex = 0;
        for(int j = 0; j < frameHeight; j++)
        {
             for(int k = 0; k < frameWidth; k++)\
             {
                 QColor color = iFrame.pixelColor(k, j);
                 image[imageIndex] = (uint8_t)color.red();
                 image[imageIndex + 1] = (uint8_t)color.green();
                 image[imageIndex + 2] = (uint8_t)color.blue();
                 image[imageIndex + 3] = (uint8_t)color.alpha();
                 imageIndex += 4;
             }
        }

        GifWriteFrame(gifwriter, image, frames.getWidth(), frames.getHeight(), 10);
        delete[] image;
    }

    GifEnd(gifwriter);
}
