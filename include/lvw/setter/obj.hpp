#pragma once

#include <cassert>
#include <lvgl/lvgl.h>

#define LVW_DEFINE_GET_OBJ() \
    lv_obj_t* get_obj() {return m_obj_setter.get_obj();}

#define LVW_DEFINE_GET_SELECTOR() \
    lv_style_selector_t get_selector() {return m_obj_setter.get_selector();}

#define LVW_DEFINE_SET_SELECTOR(setter_type) \
    setter_type& set_selector(lv_style_selector_t selector) { \
        m_obj_setter.set_selector(selector); \
        return *this; \
    }

#define LVW_DEFINE_GET_OBJ_SETTER() \
    ObjSetter& get_obj_setter() {return m_obj_setter;}

#define LVW_DEFINE_OBJ_SETTER_NECESSARY_METHODS(setter_type) \
    LVW_DEFINE_GET_OBJ(); \
    LVW_DEFINE_GET_SELECTOR(); \
    LVW_DEFINE_SET_SELECTOR(setter_type); \
    LVW_DEFINE_GET_OBJ_SETTER();

namespace lvw
{
class ObjSetter
{
public:
    ObjSetter(lv_obj_t* obj, lv_style_selector_t selector)
        : m_obj(obj), m_selector(selector)
    {
    }
    virtual ~ObjSetter()
    {
    }

    lv_obj_t* get_obj();
    lv_style_selector_t get_selector();
    ObjSetter& set_selector(lv_style_selector_t selector);

    template<typename T>
    T& get_origin_setter(T& t);

    // === Style ===
    // ## basic
    ObjSetter& bg_color_hex(uint32_t hex);
    ObjSetter& radius(lv_coord_t radius);
    ObjSetter& opa(lv_opa_t opa);
    ObjSetter& opa_cover();
    ObjSetter& opa_transp();

    // ## bg
    ObjSetter& bg_opa(lv_opa_t opa);
    ObjSetter& bg_opa_cover();
    ObjSetter& bg_opa_transp();

    // ## pad
    ObjSetter& pad_all(int32_t value);
    ObjSetter& pad_hor(int32_t value);
    ObjSetter& pad_ver(int32_t value);

    ObjSetter& pad_left(int32_t value);
    ObjSetter& pad_right(int32_t value);
    ObjSetter& pad_top(int32_t value);
    ObjSetter& pad_bottom(int32_t value);

    // ## border
    ObjSetter& border_width(int32_t value);
    ObjSetter& border_color(int32_t value);
    ObjSetter& border_opa(int32_t value);

    // ## shadow
    ObjSetter& shadow_width(int32_t value);
    ObjSetter& shadow_offset_y(int32_t value);
    ObjSetter& shadow_offset_x(int32_t value);
    ObjSetter& shadow_spread(int32_t value);
    ObjSetter& shadow_color(lv_color_t value);
    ObjSetter& shadow_opa(int32_t value);

    // ## outline
    ObjSetter& outline_width(int32_t value);
    ObjSetter& outline_color(lv_color_t value);
    ObjSetter& outline_opa(lv_opa_t value);

    // === Size/Pos/Align ===
    ObjSetter& area(lv_area_t* area);

    // ## size
    ObjSetter& size(int32_t w, int32_t h);
    ObjSetter& width(int32_t value);
    ObjSetter& height(int32_t value);

    // ## pos
    ObjSetter& pos(int32_t x, int32_t y);
    ObjSetter& x(int32_t value);
    ObjSetter& y(int32_t value);

    // ## align
    ObjSetter& align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
    ObjSetter& align_to(const lv_obj_t *base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
    ObjSetter& center();

    // ## move foreground/background
    ObjSetter& move_foreground();
    ObjSetter& move_background();

    // === Layout ===
    ObjSetter& flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place);
    ObjSetter& flex_flow(lv_flex_flow_t flow);
    ObjSetter& flex_main_place(lv_flex_align_t value);
    ObjSetter& flex_cross_place(lv_flex_align_t value);
    ObjSetter& flex_track_place(lv_flex_align_t value);
    ObjSetter& flex_grow(uint8_t value);

    ObjSetter& pad_column(lv_coord_t pad);
    ObjSetter& pad_row(lv_coord_t pad);

    // ## row
    ObjSetter& row_layout_for_center(lv_coord_t pad);
    ObjSetter& row_layout_for_start(lv_coord_t pad);
    ObjSetter& row_layout_for_end(lv_coord_t pad);
    ObjSetter& row_layout_for_end_reverse(lv_coord_t pad);

    // ## column
    ObjSetter& column_layout_for_center(lv_coord_t pad);
    ObjSetter& column_layout_for_start(lv_coord_t pad);
    ObjSetter& column_layout_for_start_reverse(lv_coord_t pad);
    ObjSetter& column_layout_for_end(lv_coord_t pad);
    ObjSetter& column_layout_for_end_reverse(lv_coord_t pad);

    // === Flag ===
    ObjSetter& add_flag(lv_obj_flag_t flag);
    ObjSetter& clear_flag(lv_obj_flag_t flag);

    // ## Function
    ObjSetter& disable_focusable();
    ObjSetter& disable_scrollable();
    ObjSetter& disable_scroll_focusable();

    // === Event ===
    ObjSetter& add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void *user_data);

    // === text ===
    ObjSetter& text_align(lv_text_align_t value);
    // ObjSetter& text_font_weight(uint8_t weight);
    ObjSetter& text_color_hex(uint32_t hex);

private:
    lv_obj_t* const m_obj;
    lv_style_selector_t m_selector;
};

inline lv_obj_t* ObjSetter::get_obj()
{
    return m_obj;
}

inline lv_style_selector_t ObjSetter::get_selector()
{
    return m_selector;
}

template<typename T>
inline T& ObjSetter::get_origin_setter(T& t) {
    assert(&t.get_obj_setter() == this);
    return t;
}

inline ObjSetter& ObjSetter::bg_color_hex(uint32_t hex) {
    lv_obj_set_style_bg_color(m_obj, lv_color_hex(hex), m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::set_selector(lv_style_selector_t selector)
{
    m_selector = selector;
    return *this;
}

inline ObjSetter& ObjSetter::radius(lv_coord_t radius) {
    lv_obj_set_style_radius(m_obj, radius, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::opa(lv_opa_t opa) {
    lv_obj_set_style_opa(m_obj, opa, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::opa_cover()
{
    lv_obj_set_style_opa(m_obj, LV_OPA_COVER, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::opa_transp()
{
    lv_obj_set_style_opa(m_obj, LV_OPA_TRANSP, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::bg_opa(lv_opa_t opa)
{
    lv_obj_set_style_bg_opa(m_obj, opa, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::bg_opa_cover()
{
    lv_obj_set_style_bg_opa(m_obj, LV_OPA_COVER, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::bg_opa_transp()
{
    lv_obj_set_style_bg_opa(m_obj, LV_OPA_TRANSP, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_all(int32_t value) {
    lv_obj_set_style_pad_all(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_hor(int32_t value) {
    lv_obj_set_style_pad_hor(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_ver(int32_t value) {
    lv_obj_set_style_pad_ver(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_left(int32_t value) {
    lv_obj_set_style_pad_left(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_right(int32_t value) {
    lv_obj_set_style_pad_right(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_top(int32_t value) {
    lv_obj_set_style_pad_top(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::pad_bottom(int32_t value) {
    lv_obj_set_style_pad_bottom(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::border_width(int32_t value) {
    lv_obj_set_style_border_width(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::border_color(int32_t value) {
    lv_obj_set_style_border_color(m_obj, lv_color_hex(value), m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::border_opa(int32_t value) {
    lv_obj_set_style_border_opa(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_width(int32_t value) {
    lv_obj_set_style_shadow_width(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_offset_y(int32_t value) {
    lv_obj_set_style_shadow_ofs_y(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_offset_x(int32_t value) {
    lv_obj_set_style_shadow_ofs_x(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_spread(int32_t value) {
    lv_obj_set_style_shadow_spread(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_color(lv_color_t value) {
    lv_obj_set_style_shadow_color(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::shadow_opa(int32_t value) {
    lv_obj_set_style_shadow_opa(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::outline_width(int32_t value) {
    lv_obj_set_style_outline_width(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::outline_color(lv_color_t value) {
    lv_obj_set_style_outline_color(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::outline_opa(lv_opa_t value) {
    lv_obj_set_style_outline_opa(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::area(lv_area_t* area) {
    lv_obj_set_pos(m_obj, area->x1, area->y1);
    lv_obj_set_size(m_obj, lv_area_get_width(area), lv_area_get_height(area));
    return *this;
}

inline ObjSetter& ObjSetter::size(int32_t w, int32_t h) {
    lv_obj_set_size(m_obj, w, h);
    return *this;
}

inline ObjSetter& ObjSetter::width(int32_t value) {
    lv_obj_set_width(m_obj, value);
    return *this;
}

inline ObjSetter& ObjSetter::height(int32_t value) {
    lv_obj_set_height(m_obj, value);
    return *this;
}

inline ObjSetter& ObjSetter::pos(int32_t x, int32_t y) {
    lv_obj_set_pos(m_obj, x, y);
    return *this;
}

inline ObjSetter& ObjSetter::x(int32_t value) {
    lv_obj_set_x(m_obj, value);
    return *this;
}

inline ObjSetter& ObjSetter::y(int32_t value) {
    lv_obj_set_y(m_obj, value);
    return *this;
}

inline ObjSetter& ObjSetter::align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_align(m_obj, align, x_ofs, y_ofs);
    return *this;
}

inline ObjSetter& ObjSetter::align_to(const lv_obj_t *base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_align_to(m_obj, base, align, x_ofs, y_ofs);
    return *this;
}

inline ObjSetter& ObjSetter::center() {
    lv_obj_center(m_obj);
    return *this;
}

inline ObjSetter & ObjSetter::move_foreground()
{
    lv_obj_move_foreground(m_obj);
    return *this;
}

inline ObjSetter & ObjSetter::move_background()
{
    lv_obj_move_background(m_obj);
    return *this;
}

inline ObjSetter& ObjSetter::flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place) {
    lv_obj_set_flex_align(m_obj, main_place, cross_place, track_cross_place);
    return *this;
}

inline ObjSetter& ObjSetter::flex_flow(lv_flex_flow_t flow) {
    lv_obj_set_style_flex_flow(m_obj, flow, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::flex_main_place(lv_flex_align_t value) {
    lv_obj_set_style_flex_main_place(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::flex_cross_place(lv_flex_align_t value) {
    lv_obj_set_style_flex_cross_place(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::flex_track_place(lv_flex_align_t value) {
    lv_obj_set_style_flex_track_place(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter& ObjSetter::flex_grow(uint8_t value) {
    lv_obj_set_style_flex_grow(m_obj, value, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::pad_column(lv_coord_t pad)
{
    lv_obj_set_style_pad_row(m_obj, pad, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::pad_row(lv_coord_t pad)
{
    lv_obj_set_style_pad_column(m_obj, pad, m_selector);
    return *this;
}

inline ObjSetter & ObjSetter::row_layout_for_center(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::row_layout_for_start(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::row_layout_for_end(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::row_layout_for_end_reverse(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_ROW_REVERSE);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::column_layout_for_center(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::column_layout_for_start(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::column_layout_for_start_reverse(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::column_layout_for_end(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::column_layout_for_end_reverse(lv_coord_t pad)
{
    lv_obj_set_flex_flow(m_obj, LV_FLEX_FLOW_ROW_REVERSE);
    lv_obj_set_flex_align(m_obj, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(m_obj, pad, 0);
    return *this;
}

inline ObjSetter & ObjSetter::add_flag(lv_obj_flag_t flag)
{
    lv_obj_add_flag(m_obj, flag);
    return *this;
}

inline ObjSetter & ObjSetter::clear_flag(lv_obj_flag_t flag)
{
    lv_obj_clear_flag(m_obj, flag);
    return *this;
}

inline ObjSetter & ObjSetter::disable_focusable()
{
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    return *this;
}

inline ObjSetter & ObjSetter::disable_scrollable()
{
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_SCROLLABLE);
    return *this;
}

inline ObjSetter& ObjSetter::disable_scroll_focusable()
{
    // checkbox bug:
    // - https://github.com/lvgl/lvgl/issues/4283
    // - https://github.com/lvgl/lvgl/commit/4404bc4d345e0361295dd13b62e2f200152aa5a3
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(m_obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    return *this;
}

inline ObjSetter & ObjSetter::add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data)
{
    lv_obj_add_event_cb(m_obj, event_cb, filter, user_data);
    return *this;
}

inline ObjSetter & ObjSetter::text_align(lv_text_align_t value)
{
    lv_obj_set_style_text_align(m_obj, value, m_selector);
    return *this;
}

// inline ObjSetter & ObjSetter::text_font_weight(uint8_t weight)
// {
//     lv_obj_set_style_text_font(m_obj, get_font_by_weight(weight), m_selector);
//     return *this;
// }

inline ObjSetter & ObjSetter::text_color_hex(uint32_t hex)
{
    lv_obj_set_style_text_color(m_obj, lv_color_hex(hex), m_selector);
    return *this;
}

} // namespace lvw
