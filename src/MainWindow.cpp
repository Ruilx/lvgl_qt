//
// Created by Ruilx on 25-12-11.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    this->resize(800, 600);
    this->setWindowTitle("LVGL Qt");

    this->setCentralWidget(this->viewer);
}

MainWindow::~MainWindow() {

}
