#include <GL/glew.h>
#include <window.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void window_show(window_t *window) {
        glfwShowWindow(window->m_handle);
}

static void window_hide(window_t *window) {
        glfwHideWindow(window->m_handle);
}

static void window_clear(window_t *window) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 0.0, 0.0, 1.0);
}

static void window_update(window_t *window) {
        glfwSwapBuffers(window->m_handle);
        glfwPollEvents();
}

static void window_toggle_fullscreen(window_t *window) {
        const GLFWvidmode *mode = glfwGetVideoMode(window->m_monitor);

        if (window->m_fullscreen == true) {
                glfwSetWindowMonitor(window->m_handle, window->m_monitor, window->m_xpos, window->m_ypos, window->m_width, window->m_height, mode->refreshRate);
        } else {
                const GLFWvidmode *mode = glfwGetVideoMode(window->m_monitor);
                glfwGetWindowPos(window->m_handle, &window->m_xpos, &window->m_ypos);
                glfwSetWindowMonitor(window->m_handle, window->m_monitor, window->m_xpos, window->m_ypos, window->m_width, window->m_height, mode->refreshRate);
        }
        
        window->m_fullscreen = !window->m_fullscreen;
}

window_t *window_new(int width, int height, char *title, bool fullscreen, bool vsync) {
        window_t *window = malloc(sizeof(window_t));
        if (window == NULL) {
                fprintf(stderr, "[%s : %d @ window_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                return NULL;
        }

        window->show = window_show;
        window->hide = window_hide;
        window->clear = window_clear;
        window->update = window_update;
        window->toggle_fullscreen = window_toggle_fullscreen;

        window->m_width = width;
        window->m_height = height;
        window->m_title = title;
        window->m_fullscreen = fullscreen;
        window->m_vsync = vsync;

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window->m_handle = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window->m_handle == NULL) {
                fprintf(stderr, "[%s : %d @ window_new()] -> glfwCreateWindow()!\n", __FILE__, __LINE__ - 2);
                free(window);
                return NULL;
        }

        glfwGetWindowPos(window->m_handle, &window->m_xpos, &window->m_ypos);
        
        window->m_monitor = glfwGetPrimaryMonitor();

        glfwMakeContextCurrent(window->m_handle);

        glfwSwapInterval(vsync);

        if (glewInit() != GLEW_OK) {
                fprintf(stderr, "[%s : %d @ window_new] -> glewInit()!\n", __FILE__, __LINE__ - 1);
                free(window);
                return NULL;
        }

        return window;
}

void window_destroy(window_t **window) {
        glfwDestroyWindow((*window)->m_handle);
        *window = NULL;
}
