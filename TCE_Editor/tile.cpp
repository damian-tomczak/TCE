#include "tile.h"

Tile::Tile(unsigned int _positionX, unsigned int _positionY, unsigned int _x, unsigned int _y, unsigned int _tileSize)
{
    bpressed = false;
    this->type = 1;
    this->x = _x;
    this->y = _y;

    this->positionX = _positionX;
    this->positionY = _positionY;
    this->tileSize = _tileSize;
}

QRectF Tile::boundingRect() const
{
    return QRectF(positionX, positionY, tileSize, tileSize);
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    switch (this->type)
    {
    case 0:
        brush.setColor(Qt::red);
        break;
    case 1:
        brush.setColor(Qt::blue);
        break;
    case 2:
        brush.setColor(Qt::yellow);
        break;
    case 3:
        brush.setColor(QColor(255, 140, 0));
        break;
    case 4:
        brush.setColor(QColor(138, 43, 226));
        break;
    }

    if (bpressed)
    {
        //TODO
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}