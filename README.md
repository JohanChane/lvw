# LVGL CPP Wrapper

## Features

- Uses lv_obj setter methods to make code clearer and easier to encapsulate custom create_ui interfaces, rather than passing numerous parameters.
- Supports lambda expressions for lv_obj event callbacks.
- Supports lambda expressions for lv_timer callback functions.

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

## Example

See [ref](./example)
