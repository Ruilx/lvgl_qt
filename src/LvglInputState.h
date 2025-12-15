#pragma once

#include <Qt>
#include <QPoint>
#include <QList>
#include <QMutex>
#include <QQueue>
#include <QHash>
#include "src/indev/lv_indev.h"

class QMouseEvent;
class QKeyEvent;

class LvglInputState {
    typedef QPair<Qt::Key, Qt::KeyboardModifiers> KeyAndModifier;

    static const QHash<KeyAndModifier, lv_key_t> keyMap;
    static const QPair<Qt::Key, Qt::Key> keyAsciiRange;

public:
    typedef struct MouseState_t {
        Qt::MouseButtons buttons;
        QPoint position;
    } MouseState;

    typedef struct KeyState_t {
        Qt::Key key;
        Qt::KeyboardModifiers modifier;
        bool pressed;
    } KeyState;

    typedef struct WheelState_t {
        QPoint numPixels;
        QPoint numDeg;
        bool pressed;
    } WheelState;

    typedef struct ButtonState_t {
        int buttonId;
        bool pressed;
    } ButtonState;

private:
    MouseState mouseState;
    QHash<Qt::Key, KeyState> keysState;
    QQueue<WheelState> wheelsState;
    QHash<int, ButtonState> buttonsState;

    QHash<int, QPoint> buttonMap;

    QMutex lock = QMutex();
public:
    explicit LvglInputState()= default;

    void addButtonId(int buttonId, const QPoint position){
        QMutexLocker locker(&this->lock);
        if(!this->buttonMap.contains(buttonId)){
            buttonMap.insert(buttonId, position);
        }
    }

    [[nodiscard]] QHash<int, QPoint> getButtonMap() const {
        return this->buttonMap;
    }

    void setMouseState(const MouseState &state){
        QMutexLocker locker(&this->lock);
        this->mouseState.buttons = state.buttons;
        this->mouseState.position = state.position;
    }

    void getMouseState(lv_indev_data_t *data) const{
        data->state = this->mouseState.buttons.testFlag(Qt::LeftButton) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
        data->point.x = this->mouseState.position.x();
        data->point.y = this->mouseState.position.y();
    }

    void setKeysState(const KeyState &state){
        QMutexLocker locker(&this->lock);
        if(this->keysState.contains(state.key)){
            if(!state.pressed){
                // released key when key in keysState
                this->keysState[state.key].pressed = false;
            }else{
                // keep key pressed
                this->keysState[state.key].pressed = true;
            }
        }else{
            if(state.pressed){
                // assign
                this->keysState.insert(state.key, state);
            }
        }
    }

    void getKeyState(lv_indev_data_t *data){
        QMutexLocker locker(&this->lock);
        if(!this->keysState.isEmpty()){
            const auto first = this->keysState.constBegin();
            if(LvglInputState::keyMap.contains(KeyAndModifier(first->key, first->modifier))){
                data->key = LvglInputState::keyMap.value(KeyAndModifier(first->key, first->modifier.testFlag(Qt::ShiftModifier) ? Qt::ShiftModifier : Qt::NoModifier));

            }else if(first->modifier == Qt::NoModifier && (first->key >= LvglInputState::keyAsciiRange.first && first->key <= LvglInputState::keyAsciiRange.second)){
                data->key = (first->key & 0xFF);
            }
            data->state = first->pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
            this->keysState.remove(first->key);
            if(!this->keysState.isEmpty()){
                data->continue_reading = true;
            }
        }else{
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }

    void setWheelState(const WheelState &state){
        QMutexLocker locker(&this->lock);
        this->wheelsState.enqueue(state);
    }

    void getWheelState(lv_indev_data_t *data){
        QMutexLocker locker(&this->lock);
        if(!this->wheelsState.isEmpty()){
            WheelState state = this->wheelsState.dequeue();
            data->enc_diff = qint16(state.numDeg.y() / 120);
            data->state = state.pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
            return;
        }else{
            data->enc_diff = 0;
            data->state = LV_INDEV_STATE_RELEASED;
            return;
        }
    }

    void setButtonState(const ButtonState &state){
        QMutexLocker locker(&this->lock);
        if(this->buttonsState.contains(state.buttonId)){
            if(!state.pressed){
                // released key when key in button state
                this->buttonsState[state.buttonId].pressed = false;
            }else{
                // keep key pressed
                this->buttonsState[state.buttonId].pressed = true;
            }
        }else{
            if(state.pressed){
                // assign
                this->buttonsState.insert(state.buttonId, state);
            }
        }
    }

    void getButtonState(lv_indev_data_t *data){
        QMutexLocker locker(&this->lock);
        if(!this->buttonsState.isEmpty()){
            auto first = this->buttonsState.constBegin();
            if(this->buttonMap.contains(first->buttonId)){
                data->btn_id = first->buttonId;
                data->state = first->pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
            }
            this->buttonsState.remove(first->buttonId);
            // var "first" maybe invalid below this comment.
            if(!this->buttonsState.isEmpty()){
                data->continue_reading = true;
            }
        }else{
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }

    ~LvglInputState() = default;

};


