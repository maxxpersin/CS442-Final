#include <stdio.h>
#include <stdbool.h>

void printBool(bool a) {
    printf("%s    ", a ? "true" : "false");
}

int main(int argc, char * argv[]) {
    int x[] = {1,2,3,4};
    int y[] = {5,3,3,2};
    int i;
    bool z;
    for (i = 0; i < 4; i++) {
        z = x[i] == y[i];
        printBool(z);
    }
    printf("\n\n");
    for (i = 0; i < 4; i++) {
        z = x[i] <= y[i];
        printBool(z);
    }
    printf("\n\n");
    for (i = 0; i < 4; i++) {
        z = x[i] >= 3 &&  y[i] <= 5;
        printBool(z);
    }
    printf("\n\n");
    for (i = 0; i < 4; i++) {
        z = x[i] > 3 ||  !(y[i] >= 5);
        printBool(z);
    }
    printf("\n");

}
