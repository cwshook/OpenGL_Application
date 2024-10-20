#include <shader.h>

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INFO_LOG_LENGTH 1024

static void shader_start(shader_t *shader, transform_t *transform) {
        glUseProgram(shader->m_program_id);

        glUniformMatrix4fv(shader->location_model_matrix, 1, GL_FALSE, &transform->m_model_matrix[0][0]);
}

static void shader_stop(void) {
        glUseProgram(0);
}

static int shader_compile(const char *shader_filepath, GLenum shader_type, unsigned int *shader_id) {
        FILE *file = NULL;
        char *file_contents = NULL;

        file = fopen(shader_filepath, "r");
        if (file == NULL) {
                fprintf(stderr, "[%s : %d @ shader_compile()] -> fopen()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        if (fseek(file, 0, SEEK_END) == -1) {
                fprintf(stderr, "[%s : %d @ shader_compile()] -> fseek()! %s!\n", __FILE__, __LINE__ - 1, strerror(errno));
                goto cleanup;
        }

        long file_length = ftell(file);
        if (file_length == -1) {
                fprintf(stderr, "[%s : %d @ shader_compile()] -> ftell()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        if (fseek(file, 0, SEEK_SET) == -1) {
                fprintf(stderr, "[%s : %d @ shader_compile()] -> fseek()! %s\n", __FILE__, __LINE__ - 1, strerror(errno));
                goto cleanup;
        }

        file_contents = malloc(sizeof(char) * (file_length + 1));
        if (file_contents == NULL) {
                fprintf(stderr, "[%s : %d @ compile_shader()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        size_t file_read = fread(file_contents, sizeof(char), file_length, file);
        if (file_read != (size_t)file_length || ferror(file)) {
                fprintf(stderr, "[%s : %d @ compile_shader()] -> fread()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        file_contents[file_length] = '\0';

        *shader_id = glCreateShader(shader_type);
        glShaderSource(*shader_id, 1, (const char *const *)&file_contents, NULL);
        glCompileShader(*shader_id);
        
        int success = 0;
        char info_log[INFO_LOG_LENGTH] = { 0 };
        glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
                glGetShaderInfoLog(*shader_id, INFO_LOG_LENGTH - 1, NULL, info_log);
                fprintf(stderr, "[%s : %d @ compile_shader()] -> Failed to compile shader '%s'!\n%s\n", __FILE__, __LINE__ - 5, shader_filepath, info_log);
                goto cleanup;
        }

        fclose(file);
        file = NULL;

        free(file_contents);
        file_contents = NULL;

        return 0;

cleanup:
        if (file != NULL) {
                fclose(file);
                file = NULL;
        }

        if (file_contents != NULL) {
                free(file_contents);
                file_contents = NULL;
        }

        return -1;
}

shader_t *shader_new(const char *vertex_filepath, const char *fragment_filepath) {
        shader_t *shader = malloc(sizeof(shader_t));
        if (shader == NULL) {
                fprintf(stderr, "[%s : %d @ shader_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                goto cleanup;
        }

        if (shader_compile(vertex_filepath, GL_VERTEX_SHADER, &shader->m_vertex_id) == -1) {
                fprintf(stderr, "[%s : %d @ shdaer_new()] -> shader_compile()!\n", __FILE__, __LINE__ - 1);
                goto cleanup;
        }

        if (shader_compile(fragment_filepath, GL_FRAGMENT_SHADER, &shader->m_fragment_id) == -1) {
                fprintf(stderr, "[%s : %d @ shader_new()] -> shader_compile()!\n", __FILE__, __LINE__ - 1);
                goto cleanup;
        }

        shader->start = shader_start;
        shader->stop = shader_stop;

        shader->m_program_id = glCreateProgram();

        glAttachShader(shader->m_program_id, shader->m_vertex_id);
        glAttachShader(shader->m_program_id, shader->m_fragment_id);

        glBindAttribLocation(shader->m_program_id, 0, "vertices");
        glBindAttribLocation(shader->m_program_id, 1, "textures");
        glLinkProgram(shader->m_program_id);
        int success = 0;
        char info_log[INFO_LOG_LENGTH];
        glGetProgramiv(shader->m_program_id, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
                fprintf(stderr, "[%ss : %d @ shader_new()] -> Failed to link shader program!\n%s\n", __FILE__, __LINE__ - 5, info_log);
                goto cleanup;
        }

        glDetachShader(shader->m_program_id, shader->m_vertex_id);
        glDetachShader(shader->m_program_id, shader->m_fragment_id);

        shader->location_model_matrix = glGetUniformLocation(shader->m_program_id, "model_matrix");

        return shader;

cleanup:
        if (shader != NULL) {
                free(shader);
                shader = NULL;
        }

        return NULL;
}

void shader_destroy(shader_t **shader) {
        glDeleteProgram((*shader)->m_program_id);

        glDeleteShader((*shader)->m_vertex_id);
        glDeleteShader((*shader)->m_fragment_id);

        free(*shader);
        *shader = NULL;
}
