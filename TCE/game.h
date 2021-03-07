#pragma once

constexpr unsigned int SCR_WIDTH = 1024;
constexpr unsigned int SCR_HEIGHT = 512;
constexpr unsigned int PRECISION = 8;
const float RAYS = 360.f / PRECISION;

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

