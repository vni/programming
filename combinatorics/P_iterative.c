#include <stdio.h>

int main(void) {
    int count = 0;
    char array[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    //char array[] = { 'a', 'b', 'c', 'd' };

    int i1, i2, i3;

    for (i1 = 0; i1 < sizeof(array); ++i1)
        for (i2 = 0; i2 < sizeof(array); ++i2)
            for (i3 = 0; i3 < sizeof(array); ++i3)
                if (i1 != i2 && i1 != i3 && i2 != i3) {
                    printf("%c %c %c\n", array[i1], array[i2], array[i3]);
                    count++;
                }

    printf("count: %d\n", count);

    return 0;
}
