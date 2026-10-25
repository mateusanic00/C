#include <stdio.h>

int main (void) {

    int number = 1;
    printf("%zu\n", sizeof(number));

    printf("Enter a number: ");
    scanf("%d", &number);
    printf("value: %d\n", number);

    if (number % 2 == 0) {
        printf("The number is par\n");
    } else {
        printf("The number is impar\n");
    }
    if (number == 2) {
        printf("You typed '2'\n");
    } else {
        printf("ok\n");
    }


    return (0);
}