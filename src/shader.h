#ifndef __SHADER_H__
#define __SHADER_H__

#include <transform.h>

typedef struct shader_s shader_t;

struct shader_s {
        void (*start)(shader_t *shader, transform_t *transform);
        void (*stop)(void);

        unsigned int location_model_matrix;

        unsigned int m_program_id;
        unsigned int m_vertex_id;
        unsigned int m_fragment_id;
};

shader_t *shader_new(const char *vertex_filepath, const char *fragment_filepath);
void shader_destroy(shader_t **shader);

#endif //__SHADER_H__
