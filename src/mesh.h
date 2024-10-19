#ifndef __MESH_H__
#define __MESH_H__

#include <lenarr.h>

typedef struct mesh_s mesh_t;
struct mesh_s {
        void (*render)(mesh_t *mesh);

        unsigned int m_vao;
        unsigned int m_vbo;
        unsigned int m_tbo;
        unsigned int m_ebo;
        flenarr_t *m_vertices;
        flenarr_t *m_textures;
        ulenarr_t *m_indices;
};

mesh_t *mesh_new(flenarr_t *vertices, flenarr_t *textures, ulenarr_t *indices);
void mesh_destroy(mesh_t **mesh);

#endif //__MESH_H__
