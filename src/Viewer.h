#pragma once

#include <QGraphicsView>

#include "Global.h"

class Viewer : public QGraphicsView {
    QPoint lastPos;
    qreal currentScale = 1.0f;
    bool mouseMovingPressed = false;
    bool mouseMovedWhilePressed = false; // 新增，用于区分右键拖拽和点击

    bool ignoreKeyAutoRepeat = false;

    bool showItemInfo = false;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

public:
    explicit Viewer(QWidget *parent = nullptr);

    ~Viewer() override {
    }

    inline void setIgnoreKeyAutoRepeat(bool enable) { this->ignoreKeyAutoRepeat = enable; }

    inline bool getIgnoreKeyAutoRepeat() const { return this->ignoreKeyAutoRepeat; }

public slots:

    void zoomIn();

    void zoomOut();

    void resetZoom();

    void fitToWindow();
};
