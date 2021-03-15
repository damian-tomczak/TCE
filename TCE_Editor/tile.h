#pragma once

#include <QPainter>
#include <QGraphicsItem>

class Tile : public QGraphicsItem
{
public:
	Tile(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
	bool bpressed;
	unsigned int type;
	unsigned int x;
	unsigned int y;

	unsigned int positionX;
	unsigned int positionY;
	
	unsigned int tileSize;
};

