#pragma once

#include "game.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

class World
{
public:
    Game* game;
	std::vector<std::vector<unsigned int>> map;
    size_t xSize;
    size_t ySize;
    float TILE_SIZE;
    float WALL_STRIP_WIDTH;

	World(float _height, Game* _game)
	{
        this->game = _game;

        std::fstream file;
        file.open("main.level", std::ios::in);
        std::string line;

        if (file.good())
        {
            std::cout << "FILE GOOD" << std::endl;
            for (int y = 0; !file.eof(); y++)
            {
                std::getline(file, line);
                map.push_back(std::vector<unsigned int>());
                for (int i = 0; i < line.size(); i++)
                {
                    map[y].push_back(line[i] - '0');
                }
            }
            map.erase(map.end() - 1);
            file.close();
        }
        else
        {
            std::cout << "main.level IS IS UNAVAILABLE!" << std::endl;
        }

        this->xSize = map[0].size();
        this->ySize = map.size();
        this->TILE_SIZE = _height / ySize;
        this->WALL_STRIP_WIDTH = game->WINDOW_WIDTH / RAYS;
        std::cout << xSize << std::endl;
        std::cout << ySize << std::endl;
	}

    int getWallContentAt(float x, float y) 
    {
        if (x < 0 || x > this->game->WINDOW_WIDTH/2 || y < 0 || y > this->game->WINDOW_HEIGHT) {
            return 0;
        }
        
        unsigned int mapGridIndexX = floor(x / this->TILE_SIZE);
        unsigned int mapGridIndexY = floor(y / this->TILE_SIZE);
        return this->map[mapGridIndexY][mapGridIndexX];
    }
};

