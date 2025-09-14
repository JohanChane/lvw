#include "my_ui_creator.hpp"

lvw::ObjSetter myui::create_obj(lv_obj_t * parent)
{
    lv_obj_t * obj = lv_obj_create(parent);

    return {obj, LV_PART_MAIN};
}

lvw::ObjSetter myui::create_obj_empty(lv_obj_t * parent)
{
    lv_obj_t * obj = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(obj, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);

    return {obj, LV_PART_MAIN};
}

lvw::ObjSetter myui::create_obj_white_bg(lv_obj_t * parent)
{
    auto obj = lv_obj_create(parent);

    // set_attribute_no_width
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);

    lv_obj_set_style_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    return {obj, LV_PART_MAIN};
}

lvw::ObjSetter myui::create_obj_black_bg(lv_obj_t * parent)
{
    auto obj = lv_obj_create(parent);

    // set_attribute_no_width
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_opa(obj, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_set_style_bg_color(obj, lv_color_hex(0x1A222C), LV_PART_MAIN);

    return lvw::ObjSetter(obj, LV_PART_MAIN);
}

lvw::BtnSetter myui::create_btn(lv_obj_t * parent)
{
    auto obj = lv_btn_create(parent);
    return {obj, LV_PART_MAIN};
}

lvw::BtnSetter myui::create_btn_green(lv_obj_t * parent, const char * txt)
{
    lv_obj_t * obj = lv_btn_create(parent);
    lv_obj_add_flag(obj, (lv_obj_flag_t)(LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE));
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x32C27F), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0x32C27F), LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x32C27F), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0x32C27F), LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(obj, LV_OPA_70, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_grad_stop(obj, 560, LV_PART_MAIN);
    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_stop(obj, 560, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN);

    create_label_white(obj)
        .text(txt)
        .get_obj_setter()
        .center();

    return lvw::BtnSetter(obj, LV_PART_MAIN);
}

lvw::LabelSetter myui::create_label(lv_obj_t * parent)
{
    auto obj = lv_label_create(parent);
    return {obj, LV_PART_MAIN};
}

lvw::LabelSetter myui::create_label_white(lv_obj_t * parent)
{
    auto obj = lv_label_create(parent);
    lv_obj_set_style_text_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    return lvw::LabelSetter(obj, LV_PART_MAIN);
}
