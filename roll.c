#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_roll(const char *);
int calculate_value(int, const char *);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Please input how you wanna roll your dice.");
    }
    else {
        int i;
        for (i = 1; i < argc; i++) {
            make_roll(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}

void make_roll(const char *expr) {
    printf("Roll %s=", expr);

    int size = strlen(expr);

    int value = calculate_value(size, expr);

    printf("%i\n", value);
}

const char* _find_symbol_in_outer_scope(int size, const char *expr, char symb) {
    int i; int scope = 0;
    for (i = 0; i < size; i++) {
        if (scope == 0 && *(expr + i) == symb) {
            return expr + i;
        }
        else if (*(expr + i) == '(') {
            scope += 1;
        }
        else if (*(expr + i) == ')') {
            scope -= 1;
        }
    }
    return NULL;
}

int _perform_symbol_check(int size, const char *expr, char symb, int *leftValue, int *rightValue) {
    const char *ptr = _find_symbol_in_outer_scope(size, expr, symb);
    if (ptr != NULL) {
        int leftSize = ptr - expr;
        *leftValue = calculate_value(leftSize, expr);
        *rightValue = calculate_value(size - leftSize - 1, ptr + 1);
        return 1;
    }
    return 0;
}

void print(int size, const char* expr) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%c", *(expr + i));
    }
}

int calculate_value(int size, const char *expr) {
    int leftValue; int rightValue;
    if (_perform_symbol_check(size, expr, '+', &leftValue, &rightValue)) {
        return leftValue + rightValue;
    }
    else if (_perform_symbol_check(size, expr, '-', &leftValue, &rightValue)) {
        return leftValue - rightValue;
    }
    else if (_perform_symbol_check(size, expr, '%', &leftValue, &rightValue)) {
        return leftValue % rightValue;
    }
    else if (_perform_symbol_check(size, expr, '/', &leftValue, &rightValue)) {
        return leftValue / rightValue;
    }
    else if (_perform_symbol_check(size, expr, '*', &leftValue, &rightValue)) {
        return leftValue * rightValue;
    }
    
    if (*expr == '(' && *(expr + size - 1) == ')') {
        return calculate_value(size - 2, expr + 1);
    }

    return atoi(expr);
}