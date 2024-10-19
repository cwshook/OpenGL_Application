#include <application.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
        application_t *application = application_new();
        if (application == NULL) {
                fprintf(stderr, "[%s : %d @ main()] -> applicationnew()!\n", __FILE__, __LINE__ - 2);
                return -1;
        }

        if (application->init(application) == -1) {
                fprintf(stderr, "[%s : %d @ main()] -> application_init()!\n", __FILE__, __LINE__ - 1);
                application_destroy(&application);
                return -1;
        }
        application->loop(application);
        application->end(application);

        application_destroy(&application);

        return 0;
}
