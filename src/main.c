#include <stdio.h>
#include "lib.h"

int main() {
    char expression[100];
    printf("Введіть математичний вираз: ");
    scanf("%s", expression);

    int result = counter(expression);

    printf("Результат: %d\n", result);

    return 0;
}
