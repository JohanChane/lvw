#pragma once

#include "obj.hpp"

namespace lvw
{
class ImgSetter
{
public:
    ImgSetter(lv_obj_t* obj, lv_style_selector_t selector)
        : m_obj_setter(obj, selector)
    {
    }

    LVW_DEFINE_OBJ_SETTER_NECESSARY_METHODS(ImgSetter);

    ImgSetter& src(const void* src);
    ImgSetter& offset_x(lv_coord_t x);
    ImgSetter& offset_y(lv_coord_t y);
    ImgSetter& angle(int16_t angle);
    ImgSetter& pivot(lv_coord_t x, lv_coord_t y);
    ImgSetter& zoom(uint16_t zoom);
    ImgSetter& antialias(bool antialias);
    // ImgSetter& size_mode(lv_img_size_mode_t mode);

private:
    ObjSetter m_obj_setter;
};

inline ImgSetter& ImgSetter::src(const void* src) {
    lv_img_set_src(m_obj_setter.get_obj(), src);
    return *this;
}

inline ImgSetter& ImgSetter::offset_x(lv_coord_t x) {
    lv_img_set_offset_x(m_obj_setter.get_obj(), x);
    return *this;
}

inline ImgSetter& ImgSetter::offset_y(lv_coord_t y) {
    lv_img_set_offset_y(m_obj_setter.get_obj(), y);
    return *this;
}

inline ImgSetter& ImgSetter::angle(int16_t angle) {
    lv_img_set_angle(m_obj_setter.get_obj(), angle);
    return *this;
}

inline ImgSetter& ImgSetter::pivot(lv_coord_t x, lv_coord_t y) {
    lv_img_set_pivot(m_obj_setter.get_obj(), x, y);
    return *this;
}

inline ImgSetter& ImgSetter::zoom(uint16_t zoom) {
    lv_img_set_zoom(m_obj_setter.get_obj(), zoom);
    return *this;
}

inline ImgSetter& ImgSetter::antialias(bool antialias) {
    lv_img_set_antialias(m_obj_setter.get_obj(), antialias);
    return *this;
}

// inline ImgSetter& ImgSetter::size_mode(lv_img_size_mode_t mode) {
//     lv_img_set_size_mode(m_obj_setter.get_obj(), mode);
//     return *this;
// }

} // namespace lvw
