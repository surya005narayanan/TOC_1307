#include <stdio.h>
#include <string.h>

#define NUM_STATES  4
#define NUM_SYMBOLS 2   /* 0 -> 'a', 1 -> 'b' */

int main(void) {
    /* Transition table: dfa[state][symbol] */
    int dfa[NUM_STATES][NUM_SYMBOLS] = {
        /*        a  b  */
        /* q0 */ {1, 3},
        /* q1 */ {1, 2},
        /* q2 */ {1, 2},
        /* q3 */ {3, 3}
    };

    int start_state = 0;
    int final_state = 1;          /* only q1 is accepting */

    char str[100];
    printf("Enter a string over {a, b}: ");
    scanf("%99s", str);

    int current = start_state;

    for (int i = 0; i < (int)strlen(str); i++) {
        int sym;
        if (str[i] == 'a')      sym = 0;
        else if (str[i] == 'b') sym = 1;
        else {
            printf("Invalid symbol '%c'. Only 'a' and 'b' are allowed.\n", str[i]);
            return 1;
        }

        int next = dfa[current][sym];
        printf("q%d --%c--> q%d\n", current, str[i], next);
        current = next;
    }

    if (current == final_state)
        printf("\nString \"%s\" is ACCEPTED (starts and ends with a)\n", str);
    else
        printf("\nString \"%s\" is REJECTED\n", str);

    return 0;
}
