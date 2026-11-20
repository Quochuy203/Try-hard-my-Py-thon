#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* max_kernel(const int* num_list, int n, int k, int* out_len) {
    if (n <= 0 || k <= 0 || k > n) {
        *out_len = 0;
        return NULL;
    }

    *out_len = n - k + 1;
    int* result = (int*)malloc((*out_len) * sizeof(int));
    if (!result) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *out_len; i++) {
        int cur_max = num_list[i];
        for (int j = 1; j < k; j++) {
            if (num_list[i + j] > cur_max) {
                cur_max = num_list[i + j];
            }
        }
        result[i] = cur_max;
    }

    return result;
}

int main(void) {
    int num_list[] = {3, 4, 5, 1, -44, 5, 10, 12, 33, 1};
    int n = sizeof(num_list) / sizeof(num_list[0]);
    int k = 3;
    int kq_len = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int* kq = max_kernel(num_list, n, k, &kq_len);
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("[");
    for (int i = 0; i < kq_len; i++) {
        printf("%d%s", kq[i], (i < kq_len - 1) ? ", " : "");
    }
    printf("]\n");

    double elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 +
                        (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Run in: %.2f µs\n", elapsed_us);

    free(kq);
    return 0;
}