#include "Viewer.h"

#include <QScrollBar>
#include <QPropertyAnimation>

#include <QMouseEvent>

#include <lvgl.h>

Viewer::Viewer(QWidget *parent) : QGraphicsView(parent) {
    QPalette pal = this->palette();
    {
        pal.setColor(QPalette::Base, Qt::black);
#if QT_VERSION_MAJOR < 6
        pal.setColor(QPalette::Background, Qt::black);
#endif
    }

    this->setPalette(pal);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMinimumSize(800, 600);

    this->setRenderHint(QPainter::TextAntialiasing);

    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    this->setInteractive(false);

    lv_init();
    rInlineDebug() << "lvgl version:" << lv_version_major() << "." << lv_version_minor() << "." << lv_version_patch();
}

void Viewer::zoomIn() {
    static constexpr qreal factor = 1.1f;
    this->currentScale *= factor;
    this->scale(factor, factor);
}

void Viewer::zoomOut() {
    static constexpr qreal factor = 1.0f / 1.1f;
    this->currentScale *= factor;
    this->scale(factor, factor);
}

void Viewer::resetZoom() {
    this->resetTransform();
    this->currentScale = 1.0f;
}

void Viewer::fitToWindow() {
    if (this->scene() == nullptr) {
        return;
    }
    const QRectF sceneRect = this->sceneRect();
    if (sceneRect.isEmpty()) {
        return;
    }

    // 计算缩放因子
    const QSizeF viewSize = this->viewport()->size();
    const qreal xScale = viewSize.width() / sceneRect.width();
    const qreal yScale = viewSize.height() / sceneRect.height();
    const qreal scaleFactor = qMin(xScale, yScale);

    this->resetTransform();
    this->scale(scaleFactor, scaleFactor);
    this->currentScale = scaleFactor;
}

void Viewer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        this->mouseMovingPressed = true;
        this->mouseMovedWhilePressed = false;
        this->lastPos = event->pos();
        // 不拦截，先不accept，等move时再决定
        // return; // 不return，继续往下
    }
    QGraphicsView::mousePressEvent(event);
}

void Viewer::mouseMoveEvent(QMouseEvent *event) {
    if (this->mouseMovingPressed) {
        const QPoint pos = event->pos();
        const int dx = pos.x() - this->lastPos.x();
        const int dy = pos.y() - this->lastPos.y();
        if (dx != 0 || dy != 0) {
            this->mouseMovedWhilePressed = true;
            this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - dx);
            this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - dy);
            this->lastPos = pos;
            event->accept();
            return;
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        if (this->mouseMovingPressed && this->mouseMovedWhilePressed) {
            // 发生了拖拽，拦截事件
            this->mouseMovingPressed = false;
            this->mouseMovedWhilePressed = false;
            event->accept();
            return;
        }
        // 没有拖拽，透传
        this->mouseMovingPressed = false;
        this->mouseMovedWhilePressed = false;
        // 不accept，继续往下
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void Viewer::wheelEvent(QWheelEvent *event) {
    const int angle = event->angleDelta().y();
    if (angle < 0) {
        this->zoomOut();
    } else {
        this->zoomIn();
    }
}

void Viewer::keyPressEvent(QKeyEvent *event) {
    QGraphicsView::keyPressEvent(event);
}

void Viewer::keyReleaseEvent(QKeyEvent *event) {
    QGraphicsView::keyReleaseEvent(event);
}

void Viewer::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    this->fitToWindow();
}
