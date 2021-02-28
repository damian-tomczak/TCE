#pragma once

#include <vector>
#include <iostream>

class World
{
public:
	std::vector<std::vector<unsigned int>> map;
    size_t xSize;
    size_t ySize;
    float sizeTile;

	World(float _height)
	{
        map =
        {   
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 2, 2, 1},
            {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 1},
            {1, 0, 3, 1, 0, 0, 0, 3, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

        xSize = map[0].size();
        ySize = map.size();
        sizeTile = _height / ySize;
        std::cout << xSize << std::endl;
        std::cout << ySize << std::endl;
	}
};

