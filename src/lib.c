#include "lib.h"

int calculator(char *expression) {
    int numStack[100];
    char opStack[100];
    int numTop = -1;
    int opTop = -1;
    int num = 0;
    int result = 0;
    int i = 0;

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            numStack[++numTop] = num;
        } else if (expression[i] == '(') {
            opStack[++opTop] = expression[i];
            i++;
        } else if (expression[i] == ')') {
            while (opTop >= 0 && opStack[opTop] != '(') {
                exponent(numStack, opStack, &numTop, &opTop);
            }

            if (opTop >= 0 && opStack[opTop] == '(')
                opTop--;  // Видаляємо відкриваючу дужку
            i++;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' ||
                   expression[i] == '%' || expression[i] == '^') {
            while (opTop >= 0 && opStack[opTop] != '(' && priority(expression[i]) <= priority(opStack[opTop])) {
                exponent(numStack, opStack, &numTop, &opTop);
            }

            opStack[++opTop] = expression[i];
            i++;
        } else {
            // Ігноруємо пробіли та інші символи
            i++;
        }
    }

    while (opTop >= 0) {
        exponent(numStack, opStack, &numTop, &opTop);
    }

    result = numStack[0];
    return result;
}

void exponent(int *numStack, char *opStack, int *numTop, int *opTop) {
    int operand2 = numStack[(*numTop)--];
    int operand1 = numStack[(*numTop)--];
    char operator = opStack[(*opTop)--];
    int partialResult;

    switch (operator) {
        case '+':
            partialResult = operand1 + operand2;
            break;
        case '-':
            partialResult = operand1 - operand2;
            break;
        case '*':
            partialResult = operand1 * operand2;
            break;
        case '/':
            partialResult = operand1 / operand2;
            break;
        case '%':
            partialResult = operand1 % operand2;
            break;
        case '^':
            partialResult = pow(operand1, operand2);
            break;
    }

    numStack[++(*numTop)] = partialResult;
}

int priority(char operator) {
    switch (operator) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;  // Дефолтне значення для невідомих операторів
    }
}
