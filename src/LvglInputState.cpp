#include "LvglInputState.h"

const QHash<LvglInputState::KeyAndModifier, lv_key_t> LvglInputState::keyMap = {
        {{Qt::Key_Up, Qt::NoModifier}, LV_KEY_UP},
        {{Qt::Key_Down, Qt::NoModifier}, LV_KEY_DOWN},
        {{Qt::Key_Right, Qt::NoModifier}, LV_KEY_RIGHT},
        {{Qt::Key_Left, Qt::NoModifier}, LV_KEY_LEFT},
        {{Qt::Key_Escape, Qt::NoModifier}, LV_KEY_ESC},
        {{Qt::Key_Delete, Qt::NoModifier}, LV_KEY_DEL},
        {{Qt::Key_Backspace, Qt::NoModifier}, LV_KEY_BACKSPACE},
        {{Qt::Key_Enter, Qt::NoModifier}, LV_KEY_ENTER},
        {{Qt::Key_Tab, Qt::NoModifier}, LV_KEY_NEXT},
        {{Qt::Key_Tab, Qt::ShiftModifier}, LV_KEY_PREV},
        {{Qt::Key_Home, Qt::NoModifier}, LV_KEY_HOME},
        {{Qt::Key_End, Qt::NoModifier}, LV_KEY_END},
};

const QPair<Qt::Key, Qt::Key> LvglInputState::keyAsciiRange = QPair<Qt::Key, Qt::Key>(Qt::Key_0, Qt::Key_AsciiTilde);

