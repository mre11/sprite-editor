// A7: Sprite Editor
// CS 3505, University of Utah, Spring 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "spriteframecollection.h"

SpriteFrameCollection::SpriteFrameCollection(int width, int height, QObject *parent)
    : QObject(parent), frameWidth(width), frameHeight(height), frames(1)
{
     addFrame(); // start out with one frame
}

SpriteFrameCollection::~SpriteFrameCollection()
{
    // delete pointers
}

void SpriteFrameCollection::addFrame()
{
    frames.push_back(new SpriteFrame(frameWidth, frameHeight, this->parent()));
}

void SpriteFrameCollection::deleteFrame(int index)
{
    frames.remove(index);
}

void SpriteFrameCollection::load()
{

}

void SpriteFrameCollection::save()
{

}
