#pragma once
#include <qgraphicsview.h>
#include <QWheelEvent>

class SceneView :
    public QGraphicsView
{
public:
    SceneView();

    virtual void SceneView::wheelEvent(QWheelEvent*);
};

