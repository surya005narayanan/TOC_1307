#include <stdio.h>
#include <string.h>

#define MAX 20

int n;                  /* number of states */
int eps[MAX][MAX];      /* eps[i][j] = 1 if there is an ε-move qi -> qj */

/* Mark every state reachable from s using only ε-moves */
void dfs(int s, int visited[]) {
    visited[s] = 1;
    for (int t = 0; t < n; t++) {
        if (eps[s][t] && !visited[t])
            dfs(t, visited);
    }
}

int main(void) {
    int m;

    printf("Enter number of states (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of states.\n");
        return 1;
    }

    printf("Enter number of ε-transitions: ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Invalid number of transitions.\n");
        return 1;
    }

    memset(eps, 0, sizeof(eps));

    printf("Enter each ε-transition as: from to   (states are numbered 0 to %d)\n", n - 1);
    for (int i = 0; i < m; i++) {
        int from, to;
        if (scanf("%d %d", &from, &to) != 2 ||
            from < 0 || from >= n || to < 0 || to >= n) {
            printf("Invalid transition.\n");
            return 1;
        }
        eps[from][to] = 1;
    }

    printf("\nε-closure of each state:\n");
    for (int s = 0; s < n; s++) {
        int visited[MAX] = {0};
        dfs(s, visited);

        printf("ε-closure(q%d) = {", s);
        int first = 1;
        for (int t = 0; t < n; t++) {
            if (visited[t]) {
                if (!first) printf(", ");
                printf("q%d", t);
                first = 0;
            }
        }
        printf("}\n");
    }

    return 0;
}
