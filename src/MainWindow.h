#pragma once

#include <QMainWindow>
#include <QApplication>

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    ~MainWindow() override;
};
