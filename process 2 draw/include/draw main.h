#ifndef DRAW_MAIN
#define DRAW_MAIN

// init
void start(int argc);
GLFWwindow* create_window();
void create_context(GLFWwindow* window, point w_position = { 0, 38 });
bool loop_render(GLFWwindow* window);

// shader
unsigned int create_program(const char*);
unsigned int create_program(const char*, const char*);

// data structure
draw_data_structure* assing_ds(const char*);

// callback
void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // !DRAW_MAIN
