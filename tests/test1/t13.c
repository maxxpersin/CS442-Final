#include <stdio.h>

int fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n-1);
}




int main(int argc, char * argv[]) {
    int x;
    scanf("%d", &x);
    printf("%d %d\n", fact(x), 2*fact(2*x));
}
