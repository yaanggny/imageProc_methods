// Josh Allmann, 11 April 2013.
// Based on "The Gray Code Filter Kernels" by G. Ben-Artzi, et al.
// http://cs.haifa.ac.il/~hagit/papers/PAMI07-GrayCodeKernels.pdf
// to compile: gcc -o gck gck.c -lm
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
static int gck_gc(int a)
{
    // return the gray code representation of a
    return (a >> 1) ^ a;
}
 
static int gck_prefix(int a, int b, int bits)
{
    // find the length of the bitwise common prefix between a and b.
    int c = 0, n = 1 << bits;
    while (n && (a & n) == (b & n)) {
        c += 1;
        n >>= 1;
    }
    return c;
}
 
static void gck_dc(int *data, int *dc, int data_len, int dst_len)
{
    int i, kern_size = dst_len - data_len + 1;
    if (data_len < kern_size) {
        fprintf(stderr, "Kernel larger than data. Exiting\n");
        exit(1);
    }
    dc[0] = data[0];
    for (i = 1; i < kern_size; i++) {
        dc[i] = data[i] + dc[i-1];
    }
    for (; i < data_len; i++) {
        dc[i] = data[i] + dc[i-1] - data[i - kern_size];
    }
    for (; i < dst_len; i++) {
        dc[i] = dc[i - 1] - data[i - kern_size];
    }
}
 
static int* gck_calc(int *data, int data_len, int kern_len, int bases)
{
    int i, j, bits, len = data_len + kern_len - 1;
    int *res = malloc(len * sizeof(int) * bases), *p = res, *q = res;   // each kernel generates a result vector of length len
    // calculate first (DC) kernel
    gck_dc(data, p, data_len, len);
 
    // rest of kernels // alpha-index length?
    bits = log2(kern_len) - 1;
    for (i = 1; i < bases; i++) {
        int prefix = gck_prefix(gck_gc(i - 1), gck_gc(i), bits);   // prefix length of alpha-index (not prefix itself)
        int delta = 1 << prefix;                                   // common prefix vector length of kernels
        int sign = (gck_gc(i) >> (bits - prefix)) & 1;
        q = p;    // q= previous filtered signal
        p += len;
        for (j = 0; j < delta; j++) 
            p[j] = -q[j];   // adjecent kernel, alpha-related
        for (; j < len; j++)
        {
            if (sign) 
                p[j] = q[j - delta] - p[j - delta] - q[j];
            else 
                p[j] = p[j - delta] - q[j - delta] - q[j];
        }
    }
 
    return res;
}
                // j=2   =q[0]-p[0]-q[2]=-1
                // j=3   =q[1]-p[1]-q[3]= 3
 
static void print_res(int *p, int w, int kern_size, int bases)
{
    int i, len = w + kern_size - 1;
    for (i = 0; i < bases; i++) {
        // printf("%3d ", p[kern_size - 1]);
        for(int j = 0; j < len; j++)
            printf("%3d ", p[j]);
        printf("\n");
        p += len;
    }
    printf("\n");
}
 
#define BASES 4
#define KERN_LEN 4
int main()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5}, *res;
    int size = sizeof(data)/sizeof(int);

    printf("dataLen, kerLen, kerCnt= %d %d %d\n", size, KERN_LEN, BASES);
    res = gck_calc(data, size, KERN_LEN, BASES);
 
    print_res(res, size, KERN_LEN, BASES);
 
    free(res);
    return 0;
}
#undef BASES
#undef KERN_LEN