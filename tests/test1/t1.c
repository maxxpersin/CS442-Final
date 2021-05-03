#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i;
    int j;
    int k;
    i = 7;
    j = 20;
    k = i+j;
    printf("%d\n", k);
    k = i-j;
    printf("%d\n", k);
    k = i*j;
    printf("%d\n", k);
    k = j/i;
    printf("%d\n", k);
    k = j%i;
    printf("%d\n", k);
    k = -i;
    printf("%d\n", k);
    k = (int) pow(i,2);  //use the exponentiation operator
    printf("%d\n", k);
}
