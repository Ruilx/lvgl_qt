#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "../LvglItem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

    QGraphicsRectItem *sceneBoundingRect = new QGraphicsRectItem(nullptr);

    void setupScene();

public:
    explicit Scene(QObject *parent = nullptr);

    ~Scene() override{
        if(this->sceneBoundingRect != nullptr){
            delete this->sceneBoundingRect;
            this->sceneBoundingRect = nullptr;
        }
    };

    void setSceneBoundingRect(const QRect &rect){
        this->sceneBoundingRect->setRect(rect);
    }

};