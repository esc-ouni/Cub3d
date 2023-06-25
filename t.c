#include <stdio.h>
#include <math.h>

int main() {
    float num1 = 123.4547999;
    float num2 = 123.454111;
    float rounded_number = round(num1 * 100) / 100.0;
    float rounded_number2 = round(num2 * 100) / 100.0;
    float d;

    d = num2 - num1;

    printf("%f\n", d);
    if (fabs(d) > 0.009)
        printf("diffrent\n");
    else
        printf("Not diffrent\n");
    return 0;
}