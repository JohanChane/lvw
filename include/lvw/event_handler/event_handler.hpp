#pragma once

#include <functional>
#include <lvgl/lvgl.h>

class EventHandler
{
public:
    EventHandler(std::function<void()>&& cb, lv_obj_t* ui_obj, lv_event_code_t filter)
        : m_cb(std::move(cb)), m_ui_obj(ui_obj), m_filter(filter)
    {
    }
    static void add_event_cb(lv_obj_t* obj, lv_event_code_t filter, std::function<void()>&& cb)
    {
        auto event_handler = new EventHandler(std::move(cb), obj, filter);

        if (filter == LV_EVENT_DEFOCUSED)
        {
            lv_obj_add_event_cb(obj, static_cast<lv_event_cb_t>(&EventHandler::call_obj_defocused_cb), filter, reinterpret_cast<void*>(event_handler));
        }
        else
        {
            lv_obj_add_event_cb(obj, static_cast<lv_event_cb_t>(&EventHandler::call_obj_other_event_cb), filter, reinterpret_cast<void*>(event_handler));
        }
        lv_obj_add_event_cb(obj, static_cast<lv_event_cb_t>(&EventHandler::on_obj_delete), LV_EVENT_DELETE, reinterpret_cast<void*>(event_handler));
    }

private:
    static void on_call(lv_event_t* ev)
    {
        auto event_handler = static_cast<EventHandler*>(lv_event_get_user_data(ev));
        event_handler->m_cb();
    }

    // Call user's defocused callback
    static void call_obj_defocused_cb(lv_event_t* ev)
    {
        on_call(ev);
    }

    // Call user's callback for other signals
    static void call_obj_other_event_cb(lv_event_t* ev)
    {
        on_call(ev);
    }

    static void on_obj_delete(lv_event_t* ev)
    {
        auto event_handler = static_cast<EventHandler*>(lv_event_get_user_data(ev));
        // If the object is deleted but has a defocused callback set, remove the defocused callback first to prevent it from being called during deletion.
        if (event_handler->m_filter == LV_EVENT_DEFOCUSED)
        {
            lv_obj_remove_event_cb_with_user_data(event_handler->m_ui_obj,
                static_cast<lv_event_cb_t>(&EventHandler::call_obj_defocused_cb),
                reinterpret_cast<void*>(event_handler));
        }
        delete event_handler;
    }

private:
    std::function<void()> m_cb;
    lv_obj_t* m_ui_obj;
    lv_event_code_t m_filter;
};
