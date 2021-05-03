#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]) {
    int low;
    int mid;
    int high;
    int temp;
    int count;
    
    scanf("%d", &count);
    while (count > 0) {
        scanf("%d%d%d", &low, &mid, &high);
        if (low > mid) {
            temp = low;
            low = mid;
            mid = temp;
        }
        if (low > high) {
            temp = low;
            low = high;
            high = temp;
        }
        if (mid > high) {
            temp = mid;
            mid = high;
            high = temp;
        }
        printf("%d %d %d\n", low, mid, high);
        count = count - 1;
    }

    
}
