#pragma once

#include <QGraphicsItem>

class Tile
{
public:
	unsigned int type;
	unsigned int x;
	unsigned int y;
	QGraphicsRectItem* rect;

	Tile(unsigned int _x, unsigned int _y)
	{
		this->type = 0;
		this->x = _x;
		this->y = _y;
	}
};

