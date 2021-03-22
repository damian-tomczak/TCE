#pragma once
#include <qgraphicsview.h>
#include <QWheelEvent>
#include <QScrollBar>

class SceneView :
    public QGraphicsView
{
public:
    SceneView();

    virtual void SceneView::wheelEvent(QWheelEvent*);
};

