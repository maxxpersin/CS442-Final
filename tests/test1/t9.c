#include <stdio.h>

int main(int argc, char * argv[]) {
	int numbers[30];
	int count;
	int i;
    int j;
    int temp;
	scanf("%d", &count);
	i = 0;
	while (i < count) {
		scanf("%d", &numbers[i]);
		i++;
	}
    
    i = 1;
    while (i < count) {
        j = i-1;
        temp = numbers[i];
        while (j >= 0 && numbers[j] < temp) {
            numbers[j+1] = numbers[j];
            j = j - 1;
        }
        numbers[j+1] = temp;
        i = i + 1;
    }
	
    printf("\n\n");
	for (i = 0; i < count; i++) {
		printf("%d ", numbers[i]);
	}
	printf("\n");
}
