#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i;
    int j;
    int k;
    int m;
    i = 3;
    j = 8;
    k = 2;
    m = i+j*k;
    printf("%d\n", m);
    m = j/i+k;
    printf("%d\n", m);
    m = k*j%i;
    printf("%d\n", m);
    m = (int) pow(8, (int) pow(2,3)); //j^k^i checks right associativity
    printf("%d\n", m);
}
