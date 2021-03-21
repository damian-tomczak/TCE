#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>
#include <QLabel>
#include <QPropertyAnimation>

#include "tile.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(unsigned int, unsigned int);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

public:
    std::vector<std::vector<Tile*>> world;

    unsigned int TILE_SIZE;
    unsigned int WORLD_SIZE;

    ~GraphicsScene();

    void getColor(int);

private:
    struct Current {
        int valueX;
        int valueY;
    };

    Current* current;

signals: 
    void comboContent(int, int);

};