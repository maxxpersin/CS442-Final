#include <stdio.h>

int fib(int n) {
    if (n <= 1) return 1;
    return fib(n-2) + fib(n-1);
}




int main(int argc, char * argv[]) {
    int x;
    scanf("%d", &x);
    printf("%d %d\n", fib(x), fib(2*x));
}
