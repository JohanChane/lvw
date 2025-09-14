#pragma once

#include "lvw/setter.hpp"

// - create 函数返回 setter 的原因是, 一般要设置 size/pos/align 等。
// - 尽量不要用函数重载, 为了更加方便地查找调用的地方。
namespace myui
{

lvw::ObjSetter create_obj(lv_obj_t * parent);
lvw::ObjSetter create_obj_empty(lv_obj_t * parent);
lvw::ObjSetter create_obj_white_bg(lv_obj_t* parent);
lvw::ObjSetter create_obj_black_bg(lv_obj_t * parent);
lvw::BtnSetter create_btn(lv_obj_t * parent);
lvw::BtnSetter create_btn_green(lv_obj_t * parent, const char * txt);
lvw::LabelSetter create_label(lv_obj_t * parent);
lvw::LabelSetter create_label_white(lv_obj_t * parent);

} // namespace myui
