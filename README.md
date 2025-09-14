# LVGL CPP Wrapper

## Features

- Uses lv_obj setter methods to make code clearer and easier to encapsulate custom create_ui interfaces, rather than passing numerous parameters.
- Supports lambda expressions for lv_obj event callbacks.
- Supports lambda expressions for lv_timer callback functions.

## Example

### lv_obj Setter

<details>
<summary>code</summary>

```cpp
auto bg_obj_setter = myui::create_obj_white_bg(lv_screen_active());
bg_obj_setter
    .size(600, 400)
    .center();

auto btn_setter = myui::create_btn(bg_obj_setter.get_obj());
btn_setter
    .get_obj_setter()
    .size(140, 48)
    .center();

auto btn_label_setter = myui::create_label(btn_setter.get_obj());
btn_label_setter
    .text_fmt("hello {}", "world")
    .get_obj_setter()
    .center()
    .get_origin_setter(btn_label_setter)        // just show get_origin_setter usage
    .text_color_hex(0x000000);
```

</details>

### Using lambda for lv_obj event callback

<details>
<summary>code</summary>

```cpp
auto btn_setter_1 = myui::create_btn(lv_screen_active())
    .get_obj_setter()
    .bg_color_hex(0x1A222C)
    .size(140, 48)
    .pos(300, 100);
auto btn_setter_2 = myui::create_btn(lv_screen_active())
    .get_obj_setter()
    .bg_color_hex(0x1A222C)
    .size(140, 48)
    .pos(300, 200);

auto btn_setter_3 = myui::create_btn(lv_screen_active())
    .get_obj_setter()
    .bg_color_hex(0x1A222C)
    .size(140, 48)
    .pos(300, 300);
auto btn_label_setter = myui::create_label(btn_setter_3.get_obj())
    .text("Click me")
    .get_obj_setter()
    .center();

EventHandler::add_event_cb(btn_setter_3.get_obj(), LV_EVENT_PRESSED, [btn_obj_1 = btn_setter_1.get_obj(), btn_obj_2 = btn_setter_2.get_obj()]() {
    auto btn_setter_1 = lvw::BtnSetter(btn_obj_1, LV_PART_MAIN);
    btn_setter_1
        .get_obj_setter()
        .bg_color_hex(0xFF0000);

    auto btn_setter_2 = lvw::BtnSetter(btn_obj_2, LV_PART_MAIN);
    btn_setter_2
        .get_obj_setter()
        .bg_color_hex(0xFF0000);
});

EventHandler::add_event_cb(btn_setter_3.get_obj(), LV_EVENT_RELEASED, [btn_obj_1 = btn_setter_1.get_obj(), btn_obj_2 = btn_setter_2.get_obj()]() {
    auto btn_setter_1 = lvw::BtnSetter(btn_obj_1, LV_PART_MAIN);
    btn_setter_1
        .get_obj_setter()
        .bg_color_hex(0x000000);

    auto btn_setter_2 = lvw::BtnSetter(btn_obj_2, LV_PART_MAIN);
    btn_setter_2
        .get_obj_setter()
        .bg_color_hex(0x000000);
});
```

</details>

### Using lambda for lv_timer event callback

<details>
<summary>code</summary>

```cpp
int cnt = 0;
LvwTimer* timer = new LvwTimer();

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
```

</details>

---

See [ref](./example)

## Run example

1. **Clone `lvw` project to your project**

```sh
cd <your_project_dir>       //  e.g. [lv_port_pc_vscode](https://github.com/lvgl/lv_port_pc_vscode)
mkdir third_party && cd third_party
git clone https://github.com/JohanChane/lvw --depth 1
```

2. **Add to your CMakeLists.txt:**

```cmake
set(LVW_BUILD_EXAMPLES ON CACHE BOOL "Build example programs" FORCE)
add_subdirectory(third_party/lvw)

# add_executable(<your_target> ...)

target_link_libraries(<your_target> <your_target_libs> lvw lvw_example)
```

3. **Call `lvw_example()`**

```c
#include <lvw_example/example.h>

void func() {
    lvw_example();
}
```
