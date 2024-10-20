#include "cglm/mat4.h"
#include <transform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void transform_update(transform_t *transform) {
        glm_translate(transform->m_model_matrix, transform->m_position);
        glm_rotate(transform->m_model_matrix, glm_rad(transform->m_rotation[0]), (vec3){1, 0, 0});
        glm_rotate(transform->m_model_matrix, glm_rad(transform->m_rotation[1]), (vec3){0, 1, 0});
        glm_rotate(transform->m_model_matrix, glm_rad(transform->m_rotation[2]), (vec3){0, 0, 1});
        glm_scale(transform->m_model_matrix, transform->m_scale);
}

static vec3 *transform_position(transform_t *transform) {
        return &transform->m_position;
}

static vec3 *transform_rotation(transform_t *transform) {
        return &transform->m_rotation;
}

static vec3 *transform_scale(transform_t *transform) {
        return &transform->m_scale;
}

transform_t *transform_new(vec3 position, vec3 rotation, vec3 scale) {
        transform_t *transform = malloc(sizeof(transform_t));
        if (transform == NULL) {
                fprintf(stderr, "[%s : %d @ transform_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        transform->update = transform_update;

        transform->position = transform_position;
        transform->rotation = transform_rotation;
        transform->scale = transform_scale;

        glm_vec3_copy(position, transform->m_position);
        glm_vec3_copy(scale, transform->m_rotation);
        glm_vec3_copy(scale, transform->m_scale);
        glm_mat4_copy(GLM_MAT4_IDENTITY, transform->m_model_matrix);
        
        return transform;

cleanup:
        if (transform != NULL) {
                free(transform);
                transform = NULL;
        }

        return NULL;
}

void transform_destroy(transform_t **transform) {
        free(*transform);
        *transform = NULL;
}
