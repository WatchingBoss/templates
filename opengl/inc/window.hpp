#ifndef WINDOW_H
#define WINDOW_H

#include "common.hpp"

#include <GLFW/glfw3.h>

/* Window */
extern void
define_window_hints();
extern GLFWwindow *
create_new_window(int, int, const char *, GLFWmonitor *, GLFWwindow *);
extern void
frasmebuffer_size_callback();
/* END Window */

/* INPUT */
extern float position_changing[3];

extern void
key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);
/* END INPUT */

#endif
