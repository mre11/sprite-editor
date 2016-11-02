// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframecollection.h"

#include <fstream>

using namespace std;

SpriteFrameCollection::SpriteFrameCollection(int width, int height, QObject *parent)
    : QObject(parent), frameWidth(width), frameHeight(height)
{
     addFrame(); // start out with one frame
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

void SpriteFrameCollection::load()
{

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

int SpriteFrameCollection::getNumbFrames()
{
    return frames.count();
}
