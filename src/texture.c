#include <texture.h>

#include <GL/glew.h>

#include <stb/stb_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void texture_bind(texture_t *texture) {
        glBindTexture(GL_TEXTURE_2D, texture->m_id);
}

static void texture_unbind(void) {
        glBindTexture(GL_TEXTURE_2D, 0);
}

texture_t *texture_new(const char *texture_filepath) {
        texture_t *texture = malloc(sizeof(texture_t));
        if (texture == NULL) {
                fprintf(stderr, "[%s : %d @ texture_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        texture->bind = texture_bind;
        texture->unbind = texture_unbind;

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        unsigned char *data = stbi_load(texture_filepath, &texture->m_width, &texture->m_height, &texture->m_channels, 0);
        if (data == NULL) {
                fprintf(stderr, "[%s : %d @ texture_new()] -> stbi_load()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        glGenTextures(1, &texture->m_id);
        glBindTexture(GL_TEXTURE_2D, texture->m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->m_width, texture->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        return texture;

cleanup:
        if (texture != NULL) {
                free(texture);
                texture = NULL;
        }

        return NULL;
}

void texture_destroy(texture_t **texture) {
        free(*texture);
        *texture = NULL;
}
