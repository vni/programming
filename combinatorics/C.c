#include <stdio.h>

void print_array(int *array, int sz)
{
    printf("[");
    for (int i = 0; i < sz; ++i) {
        printf("%d", array[i]);
        if (i < (sz-1))
            printf(", ");
    }
    printf("]\n");
}

int C(int *array, int sz, int n, int *result, int *results, int nresults)
{
    if (n <= 0 || sz <= 0) {
        return 0;
    } else if (n == 1) {
        for (int i = 0; i < sz; ++i) {
            *result = array[i];
            print_array(results, nresults);
        }
        return sz;
    } else {
        int ret = 0;
        for (int i = 0; i < sz; ++i) {
            *result = array[i];
            ret += C(array+i+1, sz-i-1, n-1, result+1, results, nresults);
        }
        return ret;
    }
}

int main(void)
{
    int array[10] = {0,1,2,3,4,5,6,7,8,9};
    int results[3];
    /* find C from 10 of 3 */
    int c = C(array, 10, 3, results, results, 3);
    printf("C from 10 of 3: %d\n", c);
    return 0;
}
