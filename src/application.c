#include <application.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "OpenGL Application"

static int application_init(application_t *application) {
        if (glfwInit() == GLFW_FALSE) {
                fprintf(stderr, "[%s : %d @ application_init()] -> glfwInit()!\n", __FILE__, __LINE__ - 1);
                return -1;
        }

        application->window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false, true);
        if (application->window == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> window_new()!\n", __FILE__, __LINE__ - 2);
                return -1;
        }

        application->window->show(application->window);

        return 0;
}

static void application_loop(application_t *application) {
        while (glfwWindowShouldClose(application->window->m_handle) == GLFW_FALSE) {
                application->window->update(application->window);
        }
}

static void application_end(application_t *application) {

}

application_t *application_new() {
        application_t *application = malloc(sizeof(application_t));
        if (application == NULL) {
                fprintf(stderr, "[%s : %d @ application_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                return NULL;
        }

        application->init = application_init;
        application->loop = application_loop;
        application->end = application_end;

        return application;
}

void application_destroy(application_t **application) {
        window_destroy(&(*application)->window);

        free(*application);
        *application = NULL;
}
