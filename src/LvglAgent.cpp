#include "LvglAgent.h"

#include <qhash.h>

#include "Global.h"
#include "lv_conf.h"

#include "lvgl_ui/LvglDemo1.h"

void LvglAgent::setupImages() {
    const QImage::Format format = this->ScreenFormat.value(LV_COLOR_DEPTH, QImage::Format_Invalid);
    if(this->screenBuffers.count() > 0) {
        for(QImage *item: this->screenBuffers) {
            if(item != nullptr) {
                delete item;
            }
            item == nullptr;
        }
        this->buf = nullptr;
        this->bufIndex = -1;
        this->screenBuffers.clear();
    }
    for(int i = 0; i < this->ScreenBufCount; i++){
        this->screenBuffers.append(new QImage(this->screenSize, format));
    }
    if (this->ScreenBufCount > 0) {
        this->buf = screenBuffers.at(0);
        this->bufIndex = 0;
    }
}

void LvglAgent::lvglInit() {
    if(!lv_is_initialized()) {
        lv_init();
    }
    if(!this->lvglCallbackIsSet) {
        this->lvglDisplayInit();
        this->lvglInputDeviceInit();
        this->lvglButtonMappingInit();
        this->lvglCallbackInit();
        this->lvglCallbackIsSet = true;
    }
}

void LvglAgent::lvglInputDeviceInit() {
    // Mouse / Touch / Pointer
    if(this->inputDevicePolicyFlags.testFlag(InputDevice_Pointer)) {
        // mouse mouse / press event
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
        lv_indev_set_user_data(indev, this);
        lv_indev_set_read_cb(indev, [](lv_indev_t * indev, lv_indev_data_t * data) {
            auto self = static_cast<LvglAgent *>(lv_indev_get_user_data(indev));
            self->lvglInputState.getMouseState(data);
            //rDebug() << "cb read POINTER at:" << data->point.x << data->point.y << data->key << data->state;
        });

        this->inputDevices.insert(InputDevice_Pointer, indev);
    }

    // Keyboard
    if(this->inputDevicePolicyFlags.testFlag(InputDevice_Keyboard)) {
        // key press / release event
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
        lv_indev_set_user_data(indev, this);
        lv_indev_set_read_cb(indev, [](lv_indev_t * indev, lv_indev_data_t * data) {
            auto self = static_cast<LvglAgent *>(lv_indev_get_user_data(indev));
            self->lvglInputState.getKeyState(data);
        });

        // group for keyboard, manage focus and nav
        if(this->globalGroup == nullptr) {
            this->globalGroup = lv_group_create();
        }
        lv_indev_set_group(indev, this->globalGroup);
        this->inputDevices.insert(InputDevice_Keyboard, indev);
    }

    // Extra button
    if(this->inputDevicePolicyFlags.testFlag(InputDevice_Button)) {
        // external button press / release event
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_BUTTON);
        lv_indev_set_user_data(indev, this);
        lv_indev_set_read_cb(indev, [](lv_indev_t * indev, lv_indev_data_t * data) {
            auto self = static_cast<LvglAgent *>(lv_indev_get_user_data(indev));
            self->lvglInputState.getButtonState(data);
        });

        this->inputDevices.insert(InputDevice_Button, indev);
    }

    // Wheel
    if(this->inputDevicePolicyFlags.testFlag(InputDevice_Wheel)) {
        // mouse wheel event
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);
        lv_indev_set_user_data(indev, this);
        lv_indev_set_read_cb(indev, [](lv_indev_t * indev, lv_indev_data_t * data) {
            auto self = static_cast<LvglAgent *>(lv_indev_get_user_data(indev));
            self->lvglInputState.getWheelState(data);
        });

        // group for wheel, manage focus and nav
        if(this->globalGroup == nullptr){
            this->globalGroup = lv_group_create();
        }
        lv_indev_set_group(indev, this->globalGroup);
        this->inputDevices.insert(InputDevice_Wheel, indev);
    }

}

void LvglAgent::lvglDisplayInit() {
    if(this->buf != nullptr) {
        const QSize screenSize = this->buf->size();
        this->display = lv_display_create(screenSize.width(), screenSize.height());
        lv_display_set_user_data(this->display, this);
        QImage *image1 = this->screenBuffers.at(0);
        QImage *image2 = nullptr;
        if(this->screenBuffers.length() > 1) {
            image2 = this->screenBuffers.at(1);
        }
        lv_display_set_buffers(
            display,
            image1->bits(),
            image2 == nullptr ? nullptr : image2->bits(),
            buf->sizeInBytes(),
            LV_DISPLAY_RENDER_MODE_PARTIAL
            //LV_DISPLAY_RENDER_MODE_FULL
        );
    }
}

void LvglAgent::lvglButtonMappingInit(){
    if(this->inputDevices.contains(InputDevice_Button)){
        auto btnMap = this->lvglInputState.getButtonMap();
        QVarLengthArray<lv_point_t, 16> btnPoints;
        for(auto i = btnMap.constBegin(); i != btnMap.constEnd(); i++){
            btnPoints.append(lv_point_t{i->x(), i->y()});
        }
        lv_indev_set_button_points(this->inputDevices.value(InputDevice_Button), btnPoints.data());
    }
}

void LvglAgent::lvglCallbackInit() {
    lv_display_set_flush_cb(this->display, [](lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
        auto *self = static_cast<LvglAgent*>(lv_display_get_user_data(disp));
        if(self != nullptr) {
            emit self->updateDisplay(self->bufIndex, QRect(QPoint(area->x1, area->y1), QPoint(area->x2, area->y2)));
            if(self->bufIndex >= 0) {
                self->buf = self->screenBuffers.at(self->bufIndex = ((++self->bufIndex) % self->screenBuffers.size()));
            }
        }
        lv_display_flush_ready(disp);
    });
}

LvglAgent::LvglAgent(const QSize &size, QObject* parent): QObject(parent) {
    this->screenSize = size;
}

LvglAgent::~LvglAgent() {
    if(this->timerId != -1){
        this->stopLvgl();
    }

    if(this->display != nullptr) {
        lv_display_delete(this->display);
    }

    for (auto screen: this->screenBuffers){
        if (screen != nullptr){
            delete screen;
            screen = nullptr;
        }
    }

    for (auto indev: this->inputDevices) {
        if(indev != nullptr) {
            lv_indev_set_group(indev, nullptr);
            lv_indev_delete(indev);
            indev = nullptr;
        }
    }
    // this->inputDevices.clear();

    if(this->globalGroup != nullptr) {
        lv_group_delete(this->globalGroup);
        this->globalGroup = nullptr;
    }

    if(lv_is_initialized()) {
        lv_deinit();
    }
}

void LvglAgent::runLvgl(LvglDemo1 *demo){
    QMutexLocker locker(&this->lock);
    if(this->buf == nullptr) {
        this->setupImages();
    }
    if(this->timerId == -1){
        this->lvglInit();
        demo->setupUi();
        this->timerId = this->startTimer(16);
        this->millis.start();
    }
}

void LvglAgent::stopLvgl(){
    QMutexLocker locker(&this->lock);
    this->killTimer(this->timerId);
    timerId = -1;
    rDebug() << "Lvgl update timer stopped";
}

void LvglAgent::timerEvent(QTimerEvent *event) {
    lv_tick_inc(this->millis.elapsed());
    this->millis.restart();
    lv_timer_handler();
    QObject::timerEvent(event);
}
