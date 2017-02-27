#include <stdio.h>

int main(void)
{
    char array[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    int count = 0;

    for (int i = 0; i < sizeof(array); ++i)
        for (int j = i + 1; j < sizeof(array); ++j)
            for (int k = j + 1; k < sizeof(array); ++k) {
                printf("%c %c %c\n", array[i], array[j], array[k]);
                count++;
            }

    printf("count: %d\n", count);
    return 0;
}
