#include "stdio.h"


void function(int *pointer) {
    print_map(*number);
}

void print_map(int n) {

}

int main(void) {
    int a, b, c;
       
    int number = 0;
    int *pointerToNumber = &number;

    function(pointerToNumber);

    return 0;
}