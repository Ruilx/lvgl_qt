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

    static constexpr QSize ScreenSize = QSize(320, 240);

    QPixmap screen = QPixmap(ScreenSize);
    bool isInitialized = false;

    LvglAgent *lvglAgent = new LvglAgent(ScreenSize, this);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
public:
    [[nodiscard]] QRectF boundingRect() const override;

    explicit LvglItem(QGraphicsItem *parent = nullptr): QGraphicsObject(parent){
        this->screen.fill(QColor(25, 25, 25));
        QString note("No Output");
        QFont font = QApplication::font(); {
            font.setPixelSize(56);
        }
        QFontMetrics fm(font);
        QSize textSize = fm.size(Qt::TextSingleLine, note);
        rDebug() << textSize;
        QPainter p(&this->screen);
        p.setFont(font);
        p.setPen(Qt::white);
        rDebug() << QPoint(qAbs(this->screen.width() - textSize.width()) / 2, qAbs(this->screen.height() - textSize.height()) / 2);
        p.drawStaticText(qAbs(this->screen.width() - textSize.width()) / 2, qAbs(this->screen.height() - textSize.height()) / 2, QStaticText(note));

        this->connect(this->lvglAgent, &LvglAgent::updateDisplay, this, &LvglItem::updateDisplay);
    }

    ~LvglItem() override = default;

    [[nodiscard]] LvglAgent * const getLvglAgent() const{
        return this->lvglAgent;
    }

public slots:
    void updateDisplay(int bufIndex, const QRect &rect);
};


