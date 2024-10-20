#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <cglm/cglm.h>

typedef struct transform_s transform_t;
struct transform_s {
        void (*update)(transform_t *transform);

        vec3 *(*position)(transform_t *transform);
        vec3 *(*rotation)(transform_t *transform);
        vec3 *(*scale)(transform_t *transform);
        mat4 *(*model_matrix)(transform_t *transform);

        vec3 m_position;
        vec3 m_rotation;
        vec3 m_scale;
        mat4 m_model_matrix;
};

transform_t *transform_new(vec3 position, vec3 rotation, vec3 scale);
void transform_destroy(transform_t **transform);

#endif //__TRANSFORM_H__
