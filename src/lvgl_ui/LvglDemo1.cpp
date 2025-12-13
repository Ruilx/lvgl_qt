//
// Created by Ruilx on 25-12-14.
//

#include "LvglDemo1.h"
#include "../Global.h"

LvglDemo1::LvglDemo1() {}

void LvglDemo1::setupUi() {
    lv_obj_t *scr = lv_scr_act();

    this->btn = lv_btn_create(scr);
    lv_obj_set_size(this->btn, 120, 50);
    lv_obj_center(this->btn);

    this->label= lv_label_create(this->btn);
    lv_label_set_text(this->label, "Hello");
    lv_obj_center(this->label);

    lv_obj_add_event_cb(this->btn, [](lv_event_t *e){
        lv_event_code_t code = lv_event_get_code(e);
        //lv_obj_t *btn = static_cast<lv_obj_t*>(lv_event_get_target(e));

        if(code == LV_EVENT_CLICKED){
            rDebug() << "Button Clicked!";

            auto self = static_cast<LvglDemo1*>(lv_event_get_user_data(e));
            lv_obj_t *label = self->label;
            lv_label_set_text(label, "Clicked!");
        }

    }, LV_EVENT_CLICKED, this);
}
