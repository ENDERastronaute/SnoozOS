
#include "./stdlib.h"

int ndigit(int number) {
    int temp = number;

    int count = 0;

    while (temp > 0) {
        count++;

        temp /= 10;
    }

    return count;
}

char* itoa(int number, char* str) {
    int count = ndigit(number); 

    int temp = number;

    int current = 0;

    for (int i = count - 1; i > 0; i--) {
        str[i] = '0' + (temp % 10);

        temp /= 10;
    }

    str[0] = '0' + (temp % 10);

    return str;
}
