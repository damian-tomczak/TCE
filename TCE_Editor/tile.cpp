#include "tile.h"

Tile::Tile(unsigned int _positionX, unsigned int _positionY, unsigned int _x, unsigned int _y, unsigned int _tileSize)
{
    bpressed = false;
    this->type = 1;
    this->indexX = _x;
    this->indexY = _y;

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
    QColor color;

    switch (this->type)
    {
    case 0:
        color = Qt::red;
        break;
    case 1:
        color = Qt::blue;
        break;
    case 2:
        color = Qt::yellow;
        break;
    case 3:
        color = QColor(255, 140, 0);
        break;
    case 4:
        color = QColor(138, 43, 226);
        break;
    }

    if (!bpressed)
    {
        color.setAlphaF(0.7);
    }

    brush.setColor(color);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}