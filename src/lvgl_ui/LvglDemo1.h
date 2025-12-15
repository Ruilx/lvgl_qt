#pragma  once

#include "lvgl.h"

class LvglDemo1 {

    lv_obj_t *btn = nullptr;
    lv_obj_t *label = nullptr;
public:
    explicit LvglDemo1();

    void setupUi();

    ~LvglDemo1(){
        if(this->btn != nullptr){
            lv_obj_delete_async(this->btn);
            this->btn = nullptr;
        }
    }
};

