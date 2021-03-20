#include "graphics_scene.h"

GraphicsScene::GraphicsScene(unsigned int _tileSize, unsigned int _worldSize) :
    TILE_SIZE(_tileSize), WORLD_SIZE(_worldSize)
{
    
    current = new Current;
    current->valueX = -1;
    current->valueY = -1;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{   
    QGraphicsItem* item = this->itemAt(mouseEvent->scenePos(), QTransform());

    for (unsigned int y = 0; y < WORLD_SIZE; y++)
    {
        for (unsigned int x = 0; x < WORLD_SIZE; x++)
        {
            if (world[y][x] == item && world[y][x]->bpressed == true)
            {
                world[y][x]->bpressed = false;
                current->valueX = -1;
                current->valueY = -1;
            }
            else if (world[y][x] == item)
            {
                if (!world[y][x]->type == 0) 
                {
                    if (world[y][x]->bpressed == false)
                    {
                        world[y][x]->bpressed = true;

                        current->valueX = x;
                        current->valueY = y;
                    }
                    else
                    {
                        world[y][x]->bpressed = false;
                        current->valueX = -1;
                        current->valueY = -1;
                    }

                    item->update();
                    goto stop;
                }
            }
            else
            {
                world[y][x]->bpressed = false;
                current->valueX = -1;
                current->valueY = -1;
            }
        }
    }

    stop:
    emit comboContent(current->valueX, current->valueY);

    update();

    QGraphicsScene::mousePressEvent(mouseEvent);
}

GraphicsScene::~GraphicsScene()
{
    unsigned int worldSize = world.size();
    for (unsigned int y = 0; y < worldSize; y++)
    {
        for (Tile* i : world[y])
        {
            delete i;
        }
    }

    world.clear();
}

void GraphicsScene::getColor(int _indexColor)
{
    qDebug() << _indexColor;

    
    if (current->valueX != -1 && current->valueY != -1)
    {
        switch (_indexColor)
        {
        case 0:
            world[current->valueY][current->valueY]->type = 1;
            break;

        case 1:
            world[current->valueY][current->valueY]->type = 2;
            break;

        case 2:
            world[current->valueY][current->valueY]->type = 3;
            break;

        case 3:
            world[current->valueY][current->valueY]->type = 4;
            break;
        }
    }
    
}
