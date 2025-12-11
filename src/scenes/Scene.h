#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT

    QGraphicsRectItem *sceneBoundingRect = new QGraphicsRectItem(nullptr);

    void setupScene();

public:
    explicit Scene(QObject *parent = nullptr);

    ~Scene() override = default;

};