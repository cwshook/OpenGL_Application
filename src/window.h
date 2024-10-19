#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GLFW/glfw3.h>

#include <stdbool.h>

typedef struct window_s window_t;

struct window_s {
        void (*show)(window_t *window);
        void (*hide)(window_t *window);
        void (*clear)(window_t *window);
        void (*update)(window_t *window);
        void (*toggle_fullscreen)(window_t *window);
        
        int m_width;
        int m_height;
        int m_xpos;
        int m_ypos;
        char *m_title;
        bool m_fullscreen;
        bool m_vsync;
        GLFWwindow *m_handle;
        GLFWmonitor *m_monitor;
};

window_t *window_new(int width, int height, char *title, bool fullscreen, bool vsync);
void window_destroy(window_t **window);

#endif //__WINDOW_H__
