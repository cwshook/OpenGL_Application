#include "mesh.h"
#include "shader.h"
#include <application.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "OpenGL Application"

#define QUAD_VERTICES ((float[]){-0.5, 0.5, 0, -0.5, -0.5, 0, 0.5, -0.5, 0, 0.5, 0.5, 0})
#define QUAD_TEXTURES ((float[]){0, 0, 0, 1, 1, 1, 1, 0})
#define QUAD_INDICES ((unsigned int[]){0, 1, 3, 3, 1, 2})

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

static int application_init(application_t *application) {
        flenarr_t *quad_vertices_lenarr = NULL;
        flenarr_t *quad_textures_lenarr = NULL;
        ulenarr_t *quad_indices_lenarr = NULL;

        if (glfwInit() == GLFW_FALSE) {
                fprintf(stderr, "[%s : %d @ application_init()] -> glfwInit()!\n", __FILE__, __LINE__ - 1);
                goto cleanup;
        }

        application->m_window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false, true);
        if (application->m_window == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> window_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        quad_vertices_lenarr = flenarr_new(QUAD_VERTICES, LENGTH(QUAD_VERTICES));
        if (quad_vertices_lenarr == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> flenarr_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        quad_textures_lenarr = flenarr_new(QUAD_TEXTURES, LENGTH(QUAD_TEXTURES));
        if (quad_textures_lenarr == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> flenarr_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        quad_indices_lenarr = ulenarr_new(QUAD_INDICES, LENGTH(QUAD_INDICES));
        if (quad_indices_lenarr == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> ulenarr_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        application->m_quad = mesh_new(quad_vertices_lenarr, quad_textures_lenarr, quad_indices_lenarr);
        if (application->m_quad == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> mesh_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        application->m_shader = shader_new("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl");
        if (application->m_shader == NULL) {
                fprintf(stderr, "[%s : %d @ application_init()] -> shader_new()!\n", __FILE__, __LINE__ - 2);
                goto cleanup;
        }

        application->m_window->show(application->m_window);

        return 0;

cleanup:
        if (application->m_window != NULL) {
                window_destroy(&application->m_window);
        }

        if (quad_vertices_lenarr != NULL) {
                flenarr_destroy(&quad_vertices_lenarr);
        }
        
        if (quad_textures_lenarr != NULL) {
                flenarr_destroy(&quad_textures_lenarr);
        }

        if (quad_indices_lenarr != NULL) {
                ulenarr_destroy(&quad_indices_lenarr);
        }

        if (application->m_quad != NULL) {
                mesh_destroy(&application->m_quad);
        }

        if (application->m_shader != NULL) {
                shader_destroy(&application->m_shader);
        }

        return -1;
}

static void application_loop(application_t *application) {
        while (glfwWindowShouldClose(application->m_window->m_handle) == GLFW_FALSE) {
                application->m_window->clear(application->m_window);

                application->m_shader->start(application->m_shader);

                application->m_quad->render(application->m_quad);

                application->m_shader->stop();
                
                application->m_window->update(application->m_window);
        }
}

static void application_end(application_t *application) {
        window_destroy(&application->m_window);

        mesh_destroy(&application->m_quad);

        shader_destroy(&application->m_shader);
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
        free(*application);
        *application = NULL;
}
