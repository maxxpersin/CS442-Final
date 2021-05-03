#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i;
    int j;
    int k;
    int m;
    scanf("%d%d%d%d",&i, &j, &k, &m);
    printf("%d %d %d %d\n",i, j, k, m);
    printf("%d %d", (int) pow(i,j) * k + m, m + k * (int) pow(i,j));
    printf("        "); //prints 8 spaces
    printf("%d %d %d %d",i, j, k, m);
    printf("\n");
}
