#include <stdio.h>
#include <stdlib.h>
#include "math/myMath.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s argv[1] argv[2] \n", argv[0]);
        return 1;
    }
    int a = atof(argv[1]);
    int b = atoi(argv[2]);
    int result = add(a, b);
    printf("%d + %d = %d\n", a, b, result);
    return 0;
}