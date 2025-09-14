#include "setter_usage.hpp"
#include "my_ui_creator.hpp"

void basic_usage() {
    auto bg_obj_setter = myui::create_obj_white_bg(lv_screen_active());
    bg_obj_setter
        .size(600, 400)
        .center();

    auto btn_setter = myui::create_btn(bg_obj_setter.get_obj());
    btn_setter
        .get_obj_setter()
        .size(140, 48)
        .center();

    auto btn_label_setter = myui::create_label(btn_setter.get_obj());
    btn_label_setter
        .text_fmt("hello {}", "world")
        .get_obj_setter()
        .center()
        .get_origin_setter(btn_label_setter)        // just show get_origin_setter usage
        .text_color_hex(0x000000);
}

void create_confirm_msg_box() {
    auto bg_setter = myui::create_obj_empty(lv_layer_top())
        .size(lv_pct(100), lv_pct(100));

    auto popup_bg_setter = myui::create_obj_black_bg(bg_setter.get_obj())
        .pad_all(40)
        .disable_scrollable()
        .size(LV_SIZE_CONTENT, 204)
        .center();

    myui::create_label_white(popup_bg_setter.get_obj())
        .text("Do you want to continue?")
        .get_obj_setter()
        .align(LV_ALIGN_TOP_MID, 0, 0);

    auto btn_layout_setter = myui::create_obj_empty(popup_bg_setter.get_obj())
        .row_layout_for_center(24)
        .size(LV_SIZE_CONTENT, LV_SIZE_CONTENT)
        .align(LV_ALIGN_BOTTOM_MID, 0, 0);

    auto cancel_btn_setter = myui::create_btn(btn_layout_setter.get_obj())
        .get_obj_setter()
        .radius(8)
        .bg_color_hex(0x243545)
        .size(140, 48);
    myui::create_label_white(cancel_btn_setter.get_obj())
        .text("No")
        .get_obj_setter()
        .center();

    myui::create_btn_green(btn_layout_setter.get_obj(), "Yes")
        .get_obj_setter().size(140, 48)
        .align(LV_ALIGN_RIGHT_MID, 0, 0);
}

void lvw_setter_usage() {
    // basic_usage();
    create_confirm_msg_box();
}
