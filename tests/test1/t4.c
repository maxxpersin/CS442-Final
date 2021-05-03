#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]) {
    int start;
    int end;
    int inc;
    int current;
    int c;
    int k;

    scanf("%d%d%d", &start, &end, &inc);
    current = start;
    while (current <= end) {
        c = (current - 32) * 5/9;
        k = (current + 460) * 5/9;
        printf("%d %d %d\n",current, c, k);
        current = current + inc;
    }
}
