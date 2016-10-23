#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include <QObject>
#include <QImage>

class SpriteFrame : public QObject
{
    Q_OBJECT
public:
    explicit SpriteFrame(int width, int height, QObject *parent = 0);

    void darken(int x, int y);
    void erase(int x, int y);
    void changeColor(int x, int y, QRgb color);
    void fillColor(int x, int y, QRgb replacementColor);
    void lighten(int x, int y);

    const QImage *getImage();

signals:
    void frameWasUpdated(const QImage *image);

public slots:
private:
    QImage image;
};

#endif // SPRITEFRAME_H
