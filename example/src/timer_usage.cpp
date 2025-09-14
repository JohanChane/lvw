#include "lvw/setter/btn.hpp"
#include "lvw/timer.hpp"
#include "my_ui_creator.hpp"
#include "timer_usage.hpp"

int cnt = 0;
LvwTimer* timer = new LvwTimer();       // If auto_delete = true, when the timer expires, LvwTimer::destroy() will be called, which triggers lv_timer_delete and the memory of m_data will be reclaimed.
                                        // However, the instance created by 'new LvwTimer' still exists. You can choose to delete the timer; even if not deleted, it only occupies a pointer-sized amount of memory after expiration.
                                        // As long as the 'new' statement is not executed multiple times, it will not cause a memory leak.
                                        // In any case, the memory allocated by `new LvwTimer` is managed by the user.

void lvw_timer_usage() {
    auto label_setter = myui::create_label(lv_screen_active());
    label_setter
        .text_fmt("cnt: {}", cnt)
        .get_obj_setter()
        .center();
    timer->create(1000, 1000, true, [label_obj = label_setter.get_obj()](LvwTimer& lvw_timer) {
        cnt += 1;
        lvw::LabelSetter(label_obj, LV_PART_MAIN)
            .text_fmt("cnt: {}", cnt);
    });
    timer->start();
}

// called by user
void when_timer_timeout() {
    delete timer;
}
