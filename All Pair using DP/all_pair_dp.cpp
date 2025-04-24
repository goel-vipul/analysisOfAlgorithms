#include <bits/stdc++.h>
using namespace std;

// Floyd-Warshall to find all-pairs shortest paths
void floydWarshall(vector<vector<int>> &matrix, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Only update if both paths exist and the new path is shorter
                if ((matrix[i][k] != -1 && matrix[k][j] != -1) &&
                    (matrix[i][j] == -1 || matrix[i][j] > matrix[i][k] + matrix[k][j])) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 4;

    // -1 means there's no direct connection between two nodes
    // actual weights can be negative, but -1 is used as "infinity"
    vector<vector<int>> graph = {
        {0, 9, -4, -1},
        {6, 0, -1, 2},
        {-1, 5, 0, -1},
        {-1, -1, 1, 0}
    };

    floydWarshall(graph, n);

    // Output the shortest path matrix
    cout << "Shortest paths between all pairs:\n";
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
