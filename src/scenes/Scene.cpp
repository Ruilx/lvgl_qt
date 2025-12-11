//
// Created by admin1 on 25-12-11.
//

#include "Scene.h"

void Scene::setupScene()
{
    this->sceneBoundingRect->setRect(0, 0, 800, 600);
    QPen pen = this->sceneBoundingRect->pen();
    {
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(Qt::darkGray);
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);
    }
    this->sceneBoundingRect->setPen(pen);
    this->setSceneRect(this->sceneBoundingRect->rect());
    this->addItem(this->sceneBoundingRect);
}

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{;
    this->setupScene();
}
