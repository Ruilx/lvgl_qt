#pragma once

#include <QGraphicsObject>
#include <QPainter>
#include <QPixmap>
#include <QApplication>
#include <QStaticText>
#include "Global.h"
#include "LvglAgent.h"

class LvglItem: public QGraphicsObject
{
    Q_OBJECT

    static constexpr QSize defaultScreenSize = QSize(320, 240);

    QPixmap screen = QPixmap(defaultScreenSize);
    bool isInitialized = false;

    LvglAgent *lvglAgent = new LvglAgent(defaultScreenSize, this);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
public:
    [[nodiscard]] QRectF boundingRect() const override;

    explicit LvglItem(QGraphicsItem *parent = nullptr);

    ~LvglItem() override = default;

    [[nodiscard]] LvglAgent * const getLvglAgent() const{
        return this->lvglAgent;
    }

    void setScreenSize(const QSize size) {
        if(!this->lvglAgent->isLvglRunning()){
            this->lvglAgent->setScreenSize(size);
            this->screen = QPixmap(size);
        }else {
            rError() << "Cannot set screen size during LVGL is running.";
        }

    }

public slots:
    void updateDisplay(int bufIndex, const QRect &rect);
};


