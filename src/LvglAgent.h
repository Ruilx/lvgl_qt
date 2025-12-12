#pragma once

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QHash>

#include "lvgl.h"

class QSize;
class LvglAgent: public QObject
{
    Q_OBJECT

    static constexpr int ScreenBufCount = 2;
public:
    static constexpr QHash<int, QImage::Format> ScreenFormat = {
        {1, QImage::Format_Mono,},
        {8, QImage::Format_Indexed8,},
        {16, QImage::Format_RGB16,},
        {24, QImage::Format_RGB888,},
        {32, QImage::Format_RGBX8888,},
    };

    enum InputDevicePolicy {
        InputDevice_None = 0x0,
        InputDevice_Pointer = 0x1,
        InputDevice_Keyboard = 0x2,
        InputDevice_Button = 0x4, // External (hardware button)
        InputDevice_Wheel = 0x8,
    };
    Q_DECLARE_FLAGS(InputDevicePolicies, InputDevicePolicy)
    Q_FLAG(InputDevicePolicies)
private:
    QVarLengthArray<QImage*, ScreenBufCount> screenBuffers;
    int bufIndex = -1;
    QImage *buf = nullptr;

    InputDevicePolicies inputDevicePolicyFlags;

    lv_display_t *display = nullptr;
    lv_group_t *globalGroup = nullptr;
    QHash<InputDevicePolicy, lv_indev_t *> inputDevices;

    QMutex lock;

    bool lvglCallbackIsSet = false;
    void lvglInit();
    void lvglInputDeviceInit();
    void lvglDisplayInit();
    void lvglCallbackInit();
public:
    explicit LvglAgent(const QSize &size, QObject *parent = nullptr);

    ~LvglAgent() override;
};

