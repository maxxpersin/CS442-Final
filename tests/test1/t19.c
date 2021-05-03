#include <stdio.h>
#include <stdbool.h>

void implication(bool a, bool b) {
    printf("%s\n", !(a && !b) ? "true" : "false");
}

int main(int argc, char * argv[]) {
    bool x;
    bool y;
    x = true;
    y = true;
    implication(x, y);
    x = true;
    y = false;
    implication(x, y);
    x = false;
    y = true;
    implication(x, y);
    x = false;
    y = false;
    implication(x, y);

}
