// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframecollection.h"

#include <fstream>
#include <sstream>

using namespace std;

SpriteFrameCollection::SpriteFrameCollection(int width, int height, QObject *parent)
    : QObject(parent), frameWidth(width), frameHeight(height)
{
     addFrame(); // start out with one frame

}

void SpriteFrameCollection::changeFrameSize(int width, int height)
{
    frames.clear();
    frameWidth = width;
    frameHeight = height;
    addFrame();
}

void SpriteFrameCollection::addFrame()
{
    frames.append(QSharedPointer<SpriteFrame>(new SpriteFrame(frameWidth, frameHeight, this)));
}

void SpriteFrameCollection::deleteFrame(int index)
{
    frames.remove(index);
}

int SpriteFrameCollection::getWidth()
{
    return frameWidth;
}

int SpriteFrameCollection::getHeight()
{
    return frameHeight;
}

void SpriteFrameCollection::open(QString filePath)
{
    string line;
    int width, height, numberOfFrames;

//    if(frameHeight != height && frameWidth != width)
//        changeFrameSize(width, height);

    ifstream inFile(filePath.toStdString());

    //open the file with a input file stream object
    //inFile.open(filePath);

    //get the first line containing the heigth and width of the canvas
    std::getline(inFile, line);
    stringstream ss(line);
    ss >> width >> height;

    //get the number of sprite frames that were saved to the file
    std::getline(inFile, line);
    stringstream ss2(line);
    ss2 >> numberOfFrames;

    frames.resize(0);

    for(int i = 0; i < numberOfFrames; i++)
    {
        addFrame();
        SpriteFrame *sf = getFrame((i));

        for(int j = 0; j < height; j++)
        {
            int r,g,b,a;
            std::getline(inFile, line);
            stringstream ss(line);

            for(int k = 0; k < width; k++)
            {
                ss >> r >> g >> b >> a;
                QColor qc(r,g,b,a);

                sf->changeColor(k, j, qc);
            }
        }
    }

    inFile.close();
}

void SpriteFrameCollection::save(QString filePath)
{
    ofstream outFile;
    outFile.open(filePath.toStdString());

    outFile << frameHeight << " " << frameWidth << '\n';
    outFile << frames.size() << '\n';

    for (auto frame : frames)
        frame->save(outFile);


}

SpriteFrame *SpriteFrameCollection::getFrame(int index)
{
    return frames.at(index).data();
}

int SpriteFrameCollection::count()
{
    return frames.count();
}
