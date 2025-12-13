#pragma once

#include <QMainWindow>
#include <QApplication>
#include "Viewer.h"
#include "lvgl_ui/LvglDemo1.h"

#include <QMenu>

class MainWindow: public QMainWindow {
    Q_OBJECT

    Viewer *viewer = new Viewer(this);

    LvglItem *lvglItem = new LvglItem(nullptr);
    LvglDemo1 *lvglDemo1 = nullptr;

    QMenu *menu = new QMenu("&Menu", this);
    QAction *runLvgl = new QAction("Run &LVGL", this);

    void setupMenus();

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    ~MainWindow() override;
};
