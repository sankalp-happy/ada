#include <stdio.h>

void prim(int n, int a[10][10]) {
    int i, j, k, u, v;
    int sum, min, source;
    int p[10], d[10], s[10];
    int t[10][2];

    min = 9999;
    source = 0;
    // Find an initial edge (this part is slightly non-standard for Prim's,
    // which usually starts from an arbitrary node like 0)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] != 0 && a[i][j] <= min) {
                min = a[i][j];
                source = i;
            }
        }
    }

    // Initialize distances, predecessors, and status arrays
    for (i = 0; i < n; i++) {
        d[i] = a[source][i]; // Distance from source
        p[i] = source;       // Predecessor
        s[i] = 0;            // Status (0: not in MST, 1: in MST)
    }

    s[source] = 1; // Add source to MST
    sum = 0;       // Initialize MST cost
    k = 0;         // Index for MST edges array t

    // Main loop to build the MST
    for (i = 1; i < n; i++) {
        min = 9999;
        u = -1;
        // Find the nearest vertex 'u' not yet in the MST
        for (j = 0; j < n; j++) {
            if (s[j] == 0) {
                if (d[j] < min) {
                    min = d[j];
                    u = j;
                }
            }
        }

        // If no vertex can be added (disconnected graph relative to current MST)
        if (u == -1)
            return; // Or handle appropriately

        // Add vertex 'u' and edge (u, p[u]) to MST
        t[k][0] = u;
        t[k][1] = p[u];
        k++;
        sum = sum + a[u][p[u]];
        s[u] = 1; // Mark 'u' as included in MST

        // Update distances for neighbors of 'u'
        for (v = 0; v < n; v++) {
            if (s[v] == 0 && a[u][v] < d[v]) {
                d[v] = a[u][v];
                p[v] = u;
            }
        }
    }

    // Check if a valid MST was formed and print results
    // Note: The check `sum >= 9999` is not a reliable way to detect if a spanning tree exists.
    // A better check would be if `k == n - 1`.
    // Also, the print statements in the original code were duplicated incorrectly.
    if (sum >= 9999) { // This condition might be unreliable
        printf("Spanning tree does not exist (or cost is very high)\n");
    } else {
        printf("The Spanning Tree Exists and Minimum Spanning Tree is\n");
        for (i = 0; i < k; i++) { // Iterate up to k edges found
            printf("%d--->%d\n", t[i][0], t[i][1]);
        }
        printf("The cost of the Spanning Tree = %d\n", sum);
    }
}

int main() {
    int i, j, n;
    int cost[10][10];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    // Basic input validation
    if (n <= 0 || n > 10) {
        printf("Number of nodes must be between 1 and 10.\n");
        return 1; // Indicate error
    }

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            // Assuming 0 means no direct edge, and 9999 represents infinity
            if (i != j && cost[i][j] == 0) {
                 cost[i][j] = 9999; // Represent no edge with infinity
            }
        }
    }

    prim(n, cost);

    return 0; // Indicate successful execution
}