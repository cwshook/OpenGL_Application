#include <lenarr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

flenarr_t *flenarr_new(float *arr, size_t length) {
        flenarr_t *lenarr = malloc(sizeof(flenarr_t));
        if (lenarr == NULL) {
                fprintf(stderr, "[%s : %d @ flenarr_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                return NULL;
        }

        if (arr == NULL) {
                lenarr->ptr = malloc(sizeof(float) * length);
                if (lenarr->ptr == NULL) {
                        fprintf(stderr, "[%s : %d @ flenarr_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                        free(lenarr);
                        return NULL;
                }
        } else {
                lenarr->ptr = arr;
        }

        lenarr->length = length;

        return lenarr;
}

void flenarr_destroy(flenarr_t **lenarr) {
        free(*lenarr);
        *lenarr = NULL;
}

ulenarr_t *ulenarr_new(unsigned int *arr, size_t length) {
        ulenarr_t *lenarr = malloc(sizeof(ulenarr_t));
        if (lenarr == NULL) {
                fprintf(stderr, "[%s : %d @ ulenarr_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                return NULL;
        }

        if (arr == NULL) {
                lenarr->ptr = malloc(sizeof(unsigned int) * length);
                if (lenarr->ptr == NULL) {
                        fprintf(stderr, "[%s : %d @ ulenarr_new()] -> malloc()! %s!\n", __FILE__, __LINE__ - 2, strerror(errno));
                        free(lenarr);
                        return NULL;
                }
        } else {
                lenarr->ptr = arr;
        }

        lenarr->length = length;

        return lenarr;
}

void ulenarr_destroy(ulenarr_t **lenarr) {
        free(*lenarr);
        *lenarr = NULL;
}
