#include <application.h>

int main(void) {
        application_t *application = application_new();

        application->init(application);
        application->loop(application);
        application->end(application);

        application_destroy(&application);

        return 0;
}
