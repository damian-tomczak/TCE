#pragma once

#include <QPainter>
#include <QGraphicsItem>

class Tile : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	Tile(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	QRectF boundingRect() const;
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
	unsigned int x;
	unsigned int y;

	unsigned int positionX;
	unsigned int positionY;
	
	unsigned int tileSize;
};

