#pragma once

#include "obj.hpp"

namespace lvw
{
class BtnSetter
{
public:
    BtnSetter(lv_obj_t* obj, lv_style_selector_t selector)
        : m_obj_setter(obj, selector)
    {
    }

    LVW_DEFINE_OBJ_SETTER_NECESSARY_METHODS(BtnSetter);

private:
    ObjSetter m_obj_setter;
};

} // namespace lvw
