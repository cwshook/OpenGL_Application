#include <mesh.h>

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void mesh_render(mesh_t *mesh) {
        glBindVertexArray(mesh->m_vao);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ebo);

        glDrawElements(GL_TRIANGLES, mesh->m_indices->length, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glBindVertexArray(0);
}

mesh_t *mesh_new(flenarr_t *vertices, flenarr_t *textures, ulenarr_t *indices) {
        mesh_t *mesh = malloc(sizeof(mesh_t));
        if (mesh == NULL) {
                fprintf(stderr, "[%s : %d @ mesh_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                return NULL;
        }

        mesh->render = mesh_render;

        mesh->m_vertices = vertices;
        mesh->m_textures = textures;
        mesh->m_indices = indices;

        glGenVertexArrays(1, &mesh->m_vao);
        glBindVertexArray(mesh->m_vao);

        glGenBuffers(1, &mesh->m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices->ptr) * vertices->length, vertices->ptr, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mesh->m_tbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->m_tbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(*textures->ptr) * textures->length, textures->ptr, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mesh->m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices->ptr) * indices->length, indices->ptr, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        return mesh;
}

void mesh_destroy(mesh_t **mesh) {
        glDeleteVertexArrays(1, &(*mesh)->m_vao);

        glDeleteBuffers(1, &(*mesh)->m_vbo);
        glDeleteBuffers(1, &(*mesh)->m_tbo);
        glDeleteBuffers(1, &(*mesh)->m_ebo);

        free(*mesh);
        *mesh = NULL;
}
