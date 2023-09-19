#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Hello, world!\n");
    printf("Goodbye, world.\n");
    int a;
    free(&a);
    return 0;
}
