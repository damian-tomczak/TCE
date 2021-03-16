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

    this->bborder = false;
}

QRectF Tile::boundingRect() const
{
    return QRectF(positionX, positionY, tileSize, tileSize);
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if(bborder)
        brush.setColor(Qt::red);
    else if (bpressed)
        brush.setColor(Qt::green);
    else
        brush.setColor(Qt::blue);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}

/*
void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!bborder)
        if (bpressed == false)
            bpressed = true;
        else
            bpressed = false;

    update();
    QGraphicsItem::mousePressEvent(event);
}
*/