#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

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
 
int main()
{
    const int lenBits = 3;
    int bits = lenBits - 1;
    int kernelCnt = pow(2, lenBits);
    for(int i = 1; i < kernelCnt; i++)
    {
        int prev = gck_gc(i - 1);
        int cur = gck_gc(i);
        int prefix = gck_prefix(prev, cur, bits);
        std::string s1 = std::bitset<lenBits>(prev).to_string();
        std::string s2 = std::bitset<lenBits>(cur).to_string();
        int sign = (cur >> (bits - prefix)) & 1;
        printf("%d %d(%s  %s): prefix= %d  delta= %d  sign= %d\n", i-1, i, s1.c_str(), s2.c_str(), prefix, int(pow(2, prefix)), sign);
    }
    
    printf("z= %d\n", (3 >> 0)&1);
    
    return 0;
}