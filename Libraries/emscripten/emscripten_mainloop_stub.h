// What does this file solves?
// - Since Dear ImGui 1.00 we took pride that most of our examples applications had their entire
//   main-loop inside the main() function. That's because:
//   - It makes the examples easier to read, keeping the code sequential.
//   - It permit the use of local variables, making it easier to try things and perform quick
//     changes when someone needs to quickly test something (vs having to structure the example
//     in order to pass data around). This is very important because people use those examples
//     to craft easy-to-past repro when they want to discuss features or report issues.
//   - It conveys at a glance that this is a no-BS framework, it won't take your main loop away from you.
//   - It is generally nice and elegant.
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <functional>
static std::function<void()>            MainLoopForEmscriptenP;
static void MainLoopForEmscripten()     { MainLoopForEmscriptenP(); }
#define EMSCRIPTEN_MAINLOOP_BEGIN       MainLoopForEmscriptenP = [&]()
#define EMSCRIPTEN_MAINLOOP_END         ; emscripten_set_main_loop(MainLoopForEmscripten, 0, true)
#else
#define EMSCRIPTEN_MAINLOOP_BEGIN
#define EMSCRIPTEN_MAINLOOP_END
#endif
