#ifndef SPRITEFRAMECOLLECTION_H
#define SPRITEFRAMECOLLECTION_H

#include <QObject>

class SpriteFrameCollection : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrameCollection(QObject *parent = 0);

signals:

public slots:
};

#endif // SPRITEFRAMECOLLECTION_H