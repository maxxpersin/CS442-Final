#include <stdio.h>
#include <stdbool.h>

void printBool(bool a) {
    printf("%s    ", a ? "true" : "false");
}

int main(int argc, char * argv[]) {
    bool x[] = {true, true, false, false};
    bool y[] = {true, false, true, false};
    int i;
    for (i = 0; i < 4; i++) {
        printBool(x[i]);
        printBool(y[i]);
        printBool(x[i] && y[i]);
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printBool(x[i]);
        printBool(y[i]);
        printBool(x[i] || y[i]);
        printf("\n");
    }
    printf("\n");
     for (i = 0; i < 4; i++) {
         printBool(x[i]);
         printBool(y[i]);
         printBool(!(x[i] && !y[i]));
         printf("\n");
     }

}
