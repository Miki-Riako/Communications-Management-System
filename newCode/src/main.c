// main.c
#include "login.c"

int main(void) {
    gtk_init(NULL, NULL);
    system(SYSTEM_CLEAR);
    startWidget();
    gtk_main();
    return 0;
    
}

// end main.c