#include "LvglItem.h"

void LvglItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, this->screen);
}

QRectF LvglItem::boundingRect() const{
    return this->screen.rect();
}

void LvglItem::updateDisplay(int bufIndex, const QRect &rect) {
    const QImage *image = this->lvglAgent->getImage(bufIndex);
    QPainter p(&this->screen);
    p.drawImage(rect, *image, rect);
    this->update(rect);
}
