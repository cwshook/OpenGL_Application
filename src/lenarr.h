#ifndef __LENARR_H__
#define __LENARR_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct flenarr_s flenarr_t;

struct flenarr_s {
        float *ptr;
        size_t length;
};

flenarr_t *flenarr_new(float *ptr, size_t length);
void flenarr_destroy(flenarr_t **lenarr);

typedef struct ulenarr_s ulenarr_t;
struct ulenarr_s {
        unsigned int *ptr;
        size_t length;
};

ulenarr_t *ulenarr_new(unsigned int *ptr, size_t length);
void ulenarr_destroy(ulenarr_t **arr);

#endif //__SIZEARR_H__
