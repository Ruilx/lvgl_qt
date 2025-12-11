#pragma once
#include <QGraphicsObject>
#include <QPainter>

class LvglItem: public QGraphicsObject
{
    Q_OBJECT

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public:
    LvglItem(QGraphicsItem *parent = nullptr): QGraphicsObject(parent)
    {

    }
};

inline void LvglItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

}
