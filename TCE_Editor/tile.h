#pragma once

#include <QPainter>
#include <QGraphicsItem>

class Tile : public QGraphicsItem
{
public:
	Tile(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	bool bborder;
	bool bpressed;

private:
	unsigned int type;
	unsigned int x;
	unsigned int y;

	unsigned int positionX;
	unsigned int positionY;
	
	unsigned int tileSize;
};

