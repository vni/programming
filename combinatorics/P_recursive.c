#include <stdio.h>

int P_recursive(char *array, int sz, char *selected, int selected_i, int selected_sz, int used, int left)
{
    if (left == 0) {
        for (int i = 0; i < selected_sz - 1; ++i)
            printf("%c ", selected[i]);
        printf("%c\n", selected[selected_sz - 1]);
        return 1;
    }

    int count = 0;
    for (int i = 0; i < sz; ++i) {
        if (used & 1<<i)
            continue;

        used |= 1 << i;

        selected[selected_i] = array[i];
        count += P_recursive(array, sz, selected, selected_i+1, selected_sz, used, left-1);

        used &= ~(1 << i);
    }

    return count;
}

int main(void)
{
    char array[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char selected[3];
    int count;
    count = P_recursive(array, 8, selected, 0, 3, 0, 3);
    printf("count: %d\n", count);
    return 0;
}
