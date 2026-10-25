#include <stdio.h> 
#define VERSION 1

double sum (double , double );
double subtract (double , double );
double divide (double , double );
double multiply (double, double );

int main (void) {
    printf("Version %d\n", VERSION);

    double num1;
    double num2;
    double result;
    char operator;

    printf("Simple-Calc\n");

    printf("Type a number: ");
    scanf(" %lf", &num1);
    printf("Type the arithmetic signal: ");
    scanf(" %c", &operator);

    printf("Type another number: ");
    scanf(" %lf", &num2);

    switch (operator)
    {
    case '+':
        result = sum(num1, num2);
        printf("%.2f\n", result);
        break;
    case '-':
        result = subtract(num1, num2);
        printf("%.2f\n", result);
        break;
    case '*': 
        result = multiply(num1, num2);
        printf("%.2f\n", result);
        break;
    case '/':
        result = divide(num1, num2);
        printf("%.2f\n", result);
        break;
    
    default:
        printf("Invalid operator!\n");
        break;
    }

    printf("num1: %.2f | operator: %c | num2: %2.f", num1, operator, num2);

    return (0);
}

double sum (double x, double y) {
    return x + y;
}
double subtract (double x, double y) {
    return x - y;
}
double divide (double x, double y) {
    return x / y;
}
double multiply (double x, double y) {
    return x * y;
}