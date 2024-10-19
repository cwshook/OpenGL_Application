#ifndef __TEXTURE_H__
#define __TEXTURE_H__

typedef struct texture_s texture_t;

struct texture_s {
        void (*bind)(texture_t *texture);
        void (*unbind)(void);

        unsigned int m_id;
        int m_width;
        int m_height;
        int m_channels;
};

texture_t *texture_new(const char *texture_filepath);
void texture_destroy(texture_t **texture);

#endif //__TEXTURE_H__
