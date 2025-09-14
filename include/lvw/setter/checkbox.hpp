#pragma once

#include "obj.hpp"

namespace lvw
{
class CheckboxSetter
{
public:
    CheckboxSetter(lv_obj_t* obj, lv_style_selector_t selector)
        : m_obj_setter(obj, selector)
    {
    }

    LVW_DEFINE_OBJ_SETTER_NECESSARY_METHODS(CheckboxSetter);

    CheckboxSetter& text(lv_obj_t *obj, const char *txt);
    CheckboxSetter& text_static(lv_obj_t *obj, const char *txt);

private:
    ObjSetter m_obj_setter;
};

inline CheckboxSetter& CheckboxSetter::text(lv_obj_t *obj, const char *txt)
{
    lv_checkbox_set_text(m_obj_setter.get_obj(), txt);
    return *this;
}

inline CheckboxSetter & CheckboxSetter::text_static(lv_obj_t * obj, const char * txt)
{
    lv_checkbox_set_text_static(m_obj_setter.get_obj(), txt);
    return *this;
}

} // namespace lvw
