#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include <QObject>

class SpriteFrame : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrame(QObject *parent = 0);

signals:

public slots:
};

#endif // SPRITEFRAME_H