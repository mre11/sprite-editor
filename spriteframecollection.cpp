#include "spriteframecollection.h"

SpriteFrameCollection::SpriteFrameCollection(int width, int height, QObject *parent)
    : QObject(parent), width(width), height(height), frames(1)
{
     addFrame(); // start out with one frame
}

void SpriteFrameCollection::addFrame()
{
    frames.push_back(new SpriteFrame(width, height, parent));
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
