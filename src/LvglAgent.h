#pragma once

#include <QObject>

class QSize;
class LvglAgent: public QObject
{
    Q_OBJECT
public:
    enum ScreenOption
    {

    };
private:
    QSize screenSize;
    quint8 *screenData;

public:
    explicit LvglAgent(const QSize &size);

    ~LvglAgent();

};