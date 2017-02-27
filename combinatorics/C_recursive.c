#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    int sz;
} buf_t;

int C_recursive(const buf_t array, int array_i, buf_t selected, int selected_i)
{
    if (selected_i == selected.sz) {
        for (int i = 0; i < selected.sz - 1; ++i)
            printf("%c ", selected.data[i]);
        printf("%c\n", selected.data[selected.sz - 1]);
        return 1;
    }
    /*
    if (array_i == array.sz) {
        if (selected_i != selected.sz) {
            printf("OOPS, (%d) array_i == array.sz (%d), but (%d) selected_i != selected.sz (%d).\n",
                    array_i, array.sz, selected_i, selected.sz);
            exit(1);
        }

        for (int i = 0; i < selected.sz - 1; ++i)
            printf("%c ", selected.data[i]);
        printf("%c\n", selected.data[selected.sz - 1]);
        return 1;
    }
    */

    int count = 0;
    for (int i = array_i; i < array.sz; ++i) {
        selected.data[selected_i] = array.data[i];
        count += C_recursive(array, i+1, selected, selected_i+1);
    }
    return count;
}

int main(void)
{
    char array[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char selected[3];
    int count = 0;

    count = C_recursive((buf_t){array, 8}, 0, (buf_t){selected, 3}, 0);
    printf("count: %d\n", count);

    return 0;
}
