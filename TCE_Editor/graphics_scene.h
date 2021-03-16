#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

#include "tile.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(unsigned int, unsigned int, QObject* parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

public:
    std::vector<std::vector<Tile*>> world;

    unsigned int TILE_SIZE;
    unsigned int WORLD_SIZE;

    ~GraphicsScene();
};