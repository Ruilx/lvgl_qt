#pragma once

class QSize;
class LvglAgent
{
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