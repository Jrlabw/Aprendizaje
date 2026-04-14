#include <stdio.h>
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;
printf("%x\n", *(p + 4 - 2));