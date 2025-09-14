#pragma once

#include <fmt/core.h>
#include "obj.hpp"

namespace lvw
{
class LabelSetter
{
public:
    LabelSetter(lv_obj_t* obj, lv_style_selector_t selector)
        : m_obj_setter(obj, selector)
    {
    }

    LVW_DEFINE_OBJ_SETTER_NECESSARY_METHODS(LabelSetter);

    LabelSetter& text(const char* text);

    // Use fmt to format strings with type-safe arguments
    template<typename... Args>
    inline LabelSetter& text_fmt(const char* fmt, Args&&... args);

    LabelSetter& text_static(const char* text);

    // LabelSetter& text_font_weight(uint8_t font_weight);
    LabelSetter& text_color_hex(uint32_t bg_color_hex);

    LabelSetter& long_mode(lv_label_long_mode_t long_mode);
    LabelSetter& recolor(bool en);
    LabelSetter& sel_start(uint32_t index);
    LabelSetter& sel_end(uint32_t index);

private:
    ObjSetter m_obj_setter;
};

inline LabelSetter & LabelSetter::text(const char * text)
{
    lv_label_set_text(m_obj_setter.get_obj(), text);
    return *this;
}

// Implementation using fmt to format strings
template<typename... Args>
inline LabelSetter& LabelSetter::text_fmt(const char* fmt, Args&&... args) {
    std::string formatted = fmt::format(fmt, std::forward<Args>(args)...);
    lv_label_set_text(m_obj_setter.get_obj(), formatted.c_str());
    return *this;
}

inline LabelSetter& LabelSetter::text_static(const char* text) {
    lv_label_set_text_static(m_obj_setter.get_obj(), text);
    return *this;
}

// inline LabelSetter& LabelSetter::text_font_weight(uint8_t font_weight) {
//     lv_obj_set_style_text_font(m_obj_setter.get_obj(), get_font_by_weight(font_weight), get_selector());
//     return *this;
// }

inline LabelSetter& LabelSetter::text_color_hex(uint32_t bg_color_hex) {
    lv_obj_set_style_text_color(m_obj_setter.get_obj(), lv_color_hex(bg_color_hex), get_selector());
    return *this;
}

inline LabelSetter& LabelSetter::long_mode(lv_label_long_mode_t long_mode) {
    lv_label_set_long_mode(m_obj_setter.get_obj(), long_mode);
    return *this;
}

inline LabelSetter& LabelSetter::recolor(bool en) {
    lv_label_set_recolor(m_obj_setter.get_obj(), en);
    return *this;
}

inline LabelSetter& LabelSetter::sel_start(uint32_t index) {
    lv_label_set_text_selection_start(m_obj_setter.get_obj(), index);
    return *this;
}

inline LabelSetter& LabelSetter::sel_end(uint32_t index) {
    lv_label_set_text_selection_end(m_obj_setter.get_obj(), index);
    return *this;
}

} // namespace lvw
