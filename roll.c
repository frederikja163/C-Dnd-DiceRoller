#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_roll(const char *);
int calculate_value(int, const char *);
int calculate_term(int, const char *);
int calculate_factor(int, const char *);

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

void make_roll(const char *roll) {
    printf("Roll %s=", roll);

    int size = strlen(roll);

    int value = calculate_value(size, roll);

    printf("%i\n", value);
}

int calculate_value(int size, const char *roll) {
    int currentValue = 0; int scope = 0; int i;
    const char* termStart = roll;

    /* Split roll into terms and add the terms together.*/
    for (i = 0; i < size; i++, roll++) {
        if (scope == 0 && i != 0 && (*roll == '+' || *roll == '-')) {
            currentValue += calculate_term(roll - termStart, termStart);
            termStart = roll;
        }
        else if (*roll == '(') {
            scope += 1;
        }
        else if (*roll == ')') {
            scope -= 1;
        }
    }
    currentValue += calculate_term(size, termStart);

    return currentValue;
}

int calculate_term(int size, const char *term) {
    int termValue = 0; int scope = 0; int i;
    const char *factorStart = term;

    /* Split the term into factors and multiply/divide the factors together.*/
    for (i = 0; i < size; i++, term++) {
        if (scope == 0 && i != 0 && (*term == '*' || *term == '/')) {
            if (*factorStart == '*') {
                /*printf("%i*%i", termValue, atoi(factorStart));*/
                termValue *= calculate_factor(size, factorStart);
            }
            else if (*factorStart == '/') {
                termValue /= calculate_factor(size, factorStart);
            }
            else {
                termValue = atoi(factorStart);
            }
            factorStart = term;
        }
        else if (*term == '(') {
            scope += 1;
        }
        else if (*term == ')') {
            scope -= 1;
        }
    }
    if (*factorStart == '*'){
        termValue *= calculate_factor(size, factorStart + 1);
    }
    else if (*factorStart == '/') {
        termValue /= calculate_factor(size, factorStart + 1);
    }
    else {
        termValue = atoi(factorStart);
    }

    return termValue;
}

int calculate_factor(int size, const char* factorStart) {
    return atoi(factorStart);
}