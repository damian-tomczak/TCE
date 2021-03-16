#include "graphics_scene.h"

GraphicsScene::GraphicsScene(unsigned int _tileSize, unsigned int _worldSize, QObject* parent) :
    QGraphicsScene(parent), TILE_SIZE(_tileSize), WORLD_SIZE(_worldSize)
{

}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsItem* item = this->itemAt(mouseEvent->scenePos(), QTransform());

    for (unsigned int y = 0; y < WORLD_SIZE; y++)
    {
        for (unsigned int x = 0; x < WORLD_SIZE; x++)
        {
            if (world[y][x] == item && world[y][x]->bpressed == true)
                world[y][x]->bpressed = false;

            else if (world[y][x] == item)
            {
                if (!world[y][x]->bborder)
                    if (world[y][x]->bpressed == false)
                        world[y][x]->bpressed = true;
                    else
                        world[y][x]->bpressed = false;
            }

            else
                world[y][x]->bpressed = false;
        }
    }

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
