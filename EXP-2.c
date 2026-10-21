#include <stdio.h>
#include <string.h>

#define NUM_STATES  3
#define NUM_SYMBOLS 2   /* 0 -> '0', 1 -> '1' */

/* Bit i of a mask represents state q_i */
#define Q0 (1 << 0)
#define Q1 (1 << 1)
#define Q2 (1 << 2)

/* Prints a set of states, e.g. {q1,q2} */
void print_set(int mask) {
    printf("{");
    int first = 1;
    for (int i = 0; i < NUM_STATES; i++) {
        if (mask & (1 << i)) {
            if (!first) printf(",");
            printf("q%d", i);
            first = 0;
        }
    }
    printf("}");
}

/* Returns 0 or 1 for a valid symbol, -1 otherwise ('o' is an alias for '0') */
int map_symbol(char c) {
    if (c == '0' || c == 'o' || c == 'O') return 0;
    if (c == '1') return 1;
    return -1;
}

int main(void) {
    /* nfa[state][symbol] = set of next states (as a bitmask) */
    int nfa[NUM_STATES][NUM_SYMBOLS] = {
        /*         0      1     */
        /* q0 */ { Q1,    0       },
        /* q1 */ { Q1,    Q1 | Q2 },
        /* q2 */ { 0,     0       }
    };

    int start_set  = Q0;
    int accept_set = Q2;      /* q2 is the only accepting state */

    char str[100];
    printf("Enter a string over {0, 1}: ");
    scanf("%99s", str);

    int current = start_set;  /* set of currently active states */
    printf("\nStart: ");
    print_set(current);
    printf("\n");

    for (int i = 0; i < (int)strlen(str); i++) {
        int sym = map_symbol(str[i]);
        if (sym == -1) {
            printf("Invalid symbol '%c'. Only 0 and 1 are allowed.\n", str[i]);
            return 1;
        }

        /* Union of the moves of every active state */
        int next = 0;
        for (int s = 0; s < NUM_STATES; s++) {
            if (current & (1 << s))
                next |= nfa[s][sym];
        }

        print_set(current);
        printf(" --%c--> ", str[i]);
        print_set(next);
        printf("\n");

        current = next;
        if (current == 0) break;   /* all paths are dead */
    }

    if (current & accept_set)
        printf("\nString \"%s\" is ACCEPTED (starts with 0 and ends with 1)\n", str);
    else
        printf("\nString \"%s\" is REJECTED\n", str);

    return 0;
}
