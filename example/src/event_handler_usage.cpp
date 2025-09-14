#include "event_handler_usage.hpp"
#include <lvw/setter.hpp>
#include <lvw/event_handler.hpp>
#include "my_ui_creator.hpp"

void event_handler_usage() {
    auto btn_setter_1 = myui::create_btn(lv_screen_active())
        .get_obj_setter()
        .bg_color_hex(0x1A222C)
        .size(140, 48)
        .pos(300, 100);
    auto btn_setter_2 = myui::create_btn(lv_screen_active())
        .get_obj_setter()
        .bg_color_hex(0x1A222C)
        .size(140, 48)
        .pos(300, 200);

    auto btn_setter_3 = myui::create_btn(lv_screen_active())
        .get_obj_setter()
        .bg_color_hex(0x1A222C)
        .size(140, 48)
        .pos(300, 300);
    auto btn_label_setter = myui::create_label(btn_setter_3.get_obj())
        .text("Click me")
        .get_obj_setter()
        .center();

    EventHandler::add_event_cb(btn_setter_3.get_obj(), LV_EVENT_PRESSED, [btn_obj_1 = btn_setter_1.get_obj(), btn_obj_2 = btn_setter_2.get_obj()]() {
        auto btn_setter_1 = lvw::BtnSetter(btn_obj_1, LV_PART_MAIN);
        btn_setter_1
            .get_obj_setter()
            .bg_color_hex(0xFF0000);

        auto btn_setter_2 = lvw::BtnSetter(btn_obj_2, LV_PART_MAIN);
        btn_setter_2
            .get_obj_setter()
            .bg_color_hex(0xFF0000);
    });

    EventHandler::add_event_cb(btn_setter_3.get_obj(), LV_EVENT_RELEASED, [btn_obj_1 = btn_setter_1.get_obj(), btn_obj_2 = btn_setter_2.get_obj()]() {
        auto btn_setter_1 = lvw::BtnSetter(btn_obj_1, LV_PART_MAIN);
        btn_setter_1
            .get_obj_setter()
            .bg_color_hex(0x000000);

        auto btn_setter_2 = lvw::BtnSetter(btn_obj_2, LV_PART_MAIN);
        btn_setter_2
            .get_obj_setter()
            .bg_color_hex(0x000000);
    });
}
