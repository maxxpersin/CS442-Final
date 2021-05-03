#include <stdio.h>
#include <stdbool.h>

int main(int argc, char * argv[]) {
    bool x;
    bool y;
    bool z;
    
    x = true;
    y = false;
    z = x && y;
    printf("%s\n", z ? "true" : "false"); //this is the way I can print true or
                                       //false in C. You should be able to say
                                       //print(z)
    z = x || y;
    printf("%s\n", z ? "true" : "false");
    z = !x;
    printf("%s\n", z ? "true" : "false");
    z = !(x && y);
    printf("%s\n", z ? "true" : "false");
    z = !x || !y;
    printf("%s\n", z ? "true" : "false");
    z = !!x;
    printf("%s\n", z ? "true" : "false");
}
