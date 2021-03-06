#pragma once

class Game
{

public:
	unsigned int WINDOW_HEIGHT;
	unsigned int WINDOW_WIDTH;

	Game(unsigned int _height, unsigned int _width)
	{
		this->WINDOW_HEIGHT = _height;
		this->WINDOW_WIDTH = _width;
	}
};

