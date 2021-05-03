#include <stdio.h>

int main(int argc, char * argv[]) {
	int numbers[30];
	int count;
	int i;
    int s;
    int p;
    int temp;
	scanf("%d", &count);
	i = 0;
	while (i < count) {
		scanf("%d", &numbers[i]);
		i++;
	}
	
    for (p = 0; p < count -1; p++) {
        s = p;
        for (i = p+1; i < count; i++) {
            if (numbers[i] < numbers[s]) {
                s = i;;
            }
        }
        temp = numbers[p];
        numbers[p] = numbers[s];
        numbers[s] = temp;
    }
    printf("\n\n");
	for (i = 0; i < count; i++) {
		printf("%d ", numbers[i]);
	}
	printf("\n");
}
