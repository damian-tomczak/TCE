#include "tile.h"

Tile::Tile(unsigned int _positionX, unsigned int _positionY, unsigned int _x, unsigned int _y, unsigned int _tileSize)
{
    bpressed = false;
    this->type = 0;
    this->x = _x;
    this->y = _y;

    this->positionX = _positionX;
    this->positionY = _positionY;
    this->tileSize = _tileSize;
    //setFlag(ItemIsMovable);
}

QRectF Tile::boundingRect() const
{
    return QRectF(positionX, positionY, tileSize, tileSize);
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (bpressed)
        brush.setColor(Qt::red);
    else
        brush.setColor(Qt::blue);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    bpressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    bpressed = false;
    update();
    QGraphicsItem::mousePressEvent(event);
}