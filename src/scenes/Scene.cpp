//
// Created by admin1 on 25-12-11.
//

#include "Scene.h"

void Scene::setupScene()
{
    QPen pen = this->sceneBoundingRect->pen();
    {
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(Qt::darkGray);
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);
    }
    this->sceneBoundingRect->setPen(pen);
    this->sceneBoundingRect->setPos(0, 0);
    this->addItem(this->sceneBoundingRect);

//    this->connect(this, &QGraphicsScene::sceneRectChanged, [this](const QRectF &rect){
//        this->setSceneBoundingRect(this);
//        rDebug() << "sceneBoundingRect" << this->sceneBoundingRect->rect();
//        this->setSceneRect(rect);
//    });
}

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    this->setupScene();
}
