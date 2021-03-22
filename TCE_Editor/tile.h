#pragma once

#include <QPainter>
#include <QGraphicsItem>

class Tile : public QGraphicsItem
{
public:
	Tile(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	bool bborder;
	bool bpressed;

	// 0 RED border 
	// 1 BLUE empty space 
	// 2 YELLOW solid 
	// 3 ORANGE solid 
	// 4 PURPLE solid 
	unsigned int type;

private:
	unsigned int indexX;
	unsigned int indexY;

	unsigned int positionX;
	unsigned int positionY;
	
	unsigned int tileSize;
};

