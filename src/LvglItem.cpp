#include "LvglItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QKeyEvent>
#include <QGraphicsSceneWheelEvent>

#include "LvglInputState.h"

void LvglItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, this->screen);
}

void LvglItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->buttons() != Qt::NoButton) {
        rDebug() << "Mouse press at:" << event->pos() << "buttons:" << event->buttons();
        this->lvglAgent->getLvglInputState().setMouseState(LvglInputState::MouseState{
            event->buttons(),
            event->pos().toPoint(),
        });
    }
    QGraphicsObject::mousePressEvent(event);
}

void LvglItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    rDebug() << "Mouse release at:" << event->pos() << "buttons:" << event->buttons();
    this->lvglAgent->getLvglInputState().setMouseState(LvglInputState::MouseState{
        Qt::NoButton,
        event->pos().toPoint(),
    });
    QGraphicsObject::mouseReleaseEvent(event);
}

void LvglItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    rDebug() << "Mouse move at:" << event->pos() << "buttons:" << event->buttons();
    this->lvglAgent->getLvglInputState().setMouseState(LvglInputState::MouseState{
        event->buttons(),
        event->pos().toPoint(),
    });
    QGraphicsObject::mouseMoveEvent(event);
}

void LvglItem::keyPressEvent(QKeyEvent *event) {
    rDebug() << "Key press:" << event->modifiers() << "key:" << event->key();
    this->lvglAgent->getLvglInputState().setKeysState(LvglInputState::KeyState{
        static_cast<Qt::Key>(event->key()),
        event->modifiers(),
        true,
    });
    QGraphicsObject::keyPressEvent(event);
}

void LvglItem::keyReleaseEvent(QKeyEvent *event) {
    rDebug() << "Key release:" << event->modifiers() << "key:" << event->key();
    this->lvglAgent->getLvglInputState().setKeysState(LvglInputState::KeyState{
        static_cast<Qt::Key>(event->key()),
        event->modifiers(),
        false,
    });
    QGraphicsObject::keyReleaseEvent(event);
}

void LvglItem::wheelEvent(QGraphicsSceneWheelEvent *event) {
    rDebug() << "Wheel turn:" << event->delta();
    this->lvglAgent->getLvglInputState().setWheelState(LvglInputState::WheelState{
        QPoint(0, event->delta()),
        QPoint(0, 0),
        event->buttons() & Qt::MiddleButton ? true : false,
    });
    QGraphicsObject::wheelEvent(event);
}

QRectF LvglItem::boundingRect() const{
    return this->screen.rect();
}

LvglItem::LvglItem(QGraphicsItem *parent): QGraphicsObject(parent) {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemIsSelectable, false);

    this->screen.fill(QColor(25, 25, 25));
    const QString note("No LVGL Output");
    QFont font = QApplication::font(); {
        font.setPixelSize(40);
    }
    const QFontMetrics fm(font);
    const QSize textSize = fm.size(Qt::TextSingleLine, note);
    rDebug() << textSize;
    QPainter p(&this->screen);
    p.setFont(font);
    p.setPen(Qt::white);
    p.drawStaticText(qAbs(this->screen.width() - textSize.width()) / 2, qAbs(this->screen.height() - textSize.height()) / 2, QStaticText(note));

    this->connect(this->lvglAgent, &LvglAgent::updateDisplay, this, &LvglItem::updateDisplay);
}

void LvglItem::updateDisplay(int bufIndex, const QRect &rect) {
    rDebug() << "Will update display:" << bufIndex << "with rect:" << rect;
    const QImage *image = this->lvglAgent->getImage(bufIndex);
    QPainter p(&this->screen);
    p.drawImage(rect, *image, rect);
    this->update(rect);
}
