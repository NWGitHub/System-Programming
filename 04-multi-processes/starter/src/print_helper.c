#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int digit;
    int count;
    int index;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <digit> <count>\n", argv[0]);
        return 1;
    }

    digit = atoi(argv[1]);
    count = atoi(argv[2]);

    for (index = 0; index < count; index++) {
        printf("%d", digit);
    }
    printf("\n");

    return 0;
}