#pragma once

#include <QMainWindow>
#include <QApplication>
#include "Viewer.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    Viewer *viewer = new Viewer(this);

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    ~MainWindow() override;
};
