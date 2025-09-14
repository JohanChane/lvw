#pragma once

#include <functional>
#include <lvgl/lvgl.h>

// Design Concept:
// - Since timer delete event is not available, use a timer with `repeat_count == -1`,
// - Meanwhile, add m_repeat_count, and delete after reaching the specified count. When `m_repeat_count == -1`, it indicates infinite repetitions.
// - LvwTimer can automatically destroy upon expiration, or can be destroyed at any time.
class LvwTimer final
{
public:
    ~LvwTimer()
    {
        destroy();
    }

    bool has_created()
    {
        return m_data;
    }

    void create(uint32_t period, int32_t repeat_count, bool is_auto_delete, std::function<void(LvwTimer&)>&& timer_cb)
    {
        if (has_created())
        {
            return;
        }

        m_data = new Data(period, repeat_count, is_auto_delete, std::move(timer_cb));
    }

    void destroy()
    {
        if (!has_created())
        {
            return;
        }

        delete_timer();
        if (m_data)
        {
            delete m_data;
            m_data = nullptr;
        }
    }

    bool is_timer_valid()
    {
        return m_data && m_data->m_lv_timer;
    }

    void delete_timer()
    {
        if (is_timer_valid())
        {
            lv_timer_del(m_data->m_lv_timer);
            m_data->m_lv_timer = nullptr;
        }
    }

    int start()
    {
        if (!has_created())
        {
            return -1;
        }

        delete_timer();
        m_data->m_repeat_count = m_data->m_origin_repeat_count;

        m_data->m_lv_timer = lv_timer_create_basic();
        lv_timer_set_period(m_data->m_lv_timer, m_data->m_period);
        lv_timer_set_repeat_count(m_data->m_lv_timer, -1);                              // lvgl default
        lv_timer_set_cb(m_data->m_lv_timer, &LvwTimer::static_timer_cb);
        lv_timer_set_user_data(m_data->m_lv_timer, reinterpret_cast<void*>(this));         // set user data

        return 0;
    }

    int set_timer_cb(const std::function<void(LvwTimer&)>&& timer_cb)
    {
        if (!has_created())
        {
            return -1;
        }

        m_data->m_timer_cb = std::move(timer_cb);

        return 0;
    }

    int set_period(uint32_t period)
    {
        if (!has_created())
        {
            return -1;
        }

        m_data->m_period = period;

        return 0;
    }

    int set_repeat_count(int32_t repeat_count)
    {
        if (!has_created())
        {
            return -1;
        }

        m_data->m_repeat_count = repeat_count;

        return 0;
    }

    int set_auto_delete(bool is_auto_delete)
    {
        if (!has_created())
        {
            return -1;
        }

        m_data->m_is_auto_delete = is_auto_delete;

        return 0;
    }

private:
    static void static_timer_cb(lv_timer_t* timer)
    {
        auto lvw_timer = reinterpret_cast<LvwTimer*>(lv_timer_get_user_data(timer));

        lvw_timer->m_data->m_timer_cb(*lvw_timer);
        // After returning from user's timer callback
        if (!lvw_timer->has_created())
        {
            return;
        }
        if (lvw_timer->is_timer_valid())
        {
            if (lvw_timer->m_data->m_repeat_count > 0)
            {
                lvw_timer->m_data->m_repeat_count--;
            }
            else if (lvw_timer->m_data->m_repeat_count == 0)
            {
                lvw_timer->delete_timer();
                if (lvw_timer->m_data->m_is_auto_delete)
                {
                    lvw_timer->destroy();
                }
            }
        }
        else
        {
            if (lvw_timer->m_data->m_is_auto_delete)
            {
                lvw_timer->destroy();
            }
        }
    }

private:
    struct Data
    {
        Data(uint32_t period, int32_t repeat_count, bool is_auto_delete, const std::function<void(LvwTimer&)>&& timer_cb)
            : m_period(period), m_repeat_count(repeat_count), m_is_auto_delete(is_auto_delete), m_timer_cb(std::move(timer_cb)), m_origin_repeat_count(repeat_count)
        {
        }

        uint32_t m_period;
        int32_t m_repeat_count;
        bool m_is_auto_delete;                 // Whether to automatically destroy when timer expires
        std::function<void(LvwTimer&)> m_timer_cb;
        lv_timer_t* m_lv_timer = nullptr;      // This should not be exposed externally
        const int32_t m_origin_repeat_count;
    };
    Data* m_data = nullptr;
};
