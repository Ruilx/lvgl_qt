//
// Created by Ruilx on 25-12-11.
//

#include "MainWindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    this->resize(800, 600);
    this->setWindowTitle("LVGL Qt");

    this->setCentralWidget(this->viewer);

    this->setupMenus();

    this->lvglItem->setPos(0, 0);
    this->viewer->scene()->addItem(this->lvglItem);
    this->viewer->setSceneRect(this->lvglItem->boundingRect());
}

MainWindow::~MainWindow() {
    if(this->lvglItem != nullptr){
        delete this->lvglItem;
        this->lvglItem = nullptr;
    }
    if(this->lvglDemo1 != nullptr){
        delete this->lvglDemo1;
        this->lvglDemo1 = nullptr;
    }
}

void MainWindow::setupMenus() {
    connect(this->runLvgl, &QAction::triggered, [this](bool){
        this->lvglDemo1 = new LvglDemo1();
        this->lvglItem->getLvglAgent()->runLvgl(this->lvglDemo1);
    });
    this->menu->addAction(runLvgl);


    this->menuBar()->addMenu(this->menu);


}
