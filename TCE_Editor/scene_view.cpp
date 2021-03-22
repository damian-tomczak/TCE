#include "scene_view.h"

SceneView::SceneView()
{
}

void SceneView::wheelEvent(QWheelEvent* event)
{
    qreal deltaScale = 1;
    deltaScale += event->angleDelta().y() > 0 ? 0.1 : -0.1;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(deltaScale, deltaScale);
}