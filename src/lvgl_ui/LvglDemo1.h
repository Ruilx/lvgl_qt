#pragma  once

#include "lvgl.h"

class LvglDemo1 {

    lv_obj_t *btn = nullptr;
    lv_obj_t *label = nullptr;
public:
    explicit LvglDemo1();

    void setupUi();

    ~LvglDemo1(){
        if(this->label != nullptr){
            lv_obj_delete(this->label);
            this->label = nullptr;
        }
        if(this->btn != nullptr){
            lv_obj_delete(this->btn);
            this->btn = nullptr;
        }
    }
};

