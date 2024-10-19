#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <window.h>
#include <mesh.h>

typedef struct application_s application_t;

struct application_s {
        int (*init)(application_t *application);
        void (*loop)(application_t *application);
        void (*end)(application_t *application);

        window_t *m_window;
        mesh_t *m_quad;
};

application_t *application_new();
void application_destroy(application_t **application);

#endif //__APPLICATION_H__
