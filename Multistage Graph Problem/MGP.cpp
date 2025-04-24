#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Representing "no connection" with a large number

// Function to count the number of stages in a multistage graph
int countStages(const vector<vector<int>>& graph) {
    int stages = 1; // Start from stage 1 for the source node
    int current = 0;

    for (int next = current + 1; next < graph.size(); next++) {
        if (graph[current][next] != INF) {
            current = next;
            stages++;
        }
    }

    return stages;
}

// Function to compute and print the Minimum Cost Path in a Multistage Graph
void findMinCostPath(vector<vector<int>>& graph, int stages) {
    int n = graph.size();
    vector<int> minCost(n, INF); // Stores minimum cost from each node to destination
    vector<int> nextNode(n, -1); // Stores the next node in the minimum-cost path

    minCost[n - 1] = 0; // Cost to reach from destination to destination is 0

    // Start computing from the second last node towards the source
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != INF && graph[i][j] != 0) {
                if (graph[i][j] + minCost[j] < minCost[i]) {
                    minCost[i] = graph[i][j] + minCost[j];
                    nextNode[i] = j;
                }
            }
        }
    }

    // Construct the minimum-cost path from nextNode[]
    vector<int> path(stages);
    path[0] = 1;          // Start node (1-based index)
    path[stages - 1] = n; // Destination node

    for (int i = 1; i < stages - 1; i++) {
        path[i] = nextNode[path[i - 1] - 1] + 1; // Convert back to 1-based indexing
    }

    // Output the minimum-cost path
    cout << "\nMinimum-cost path: ";
    for (int i = 0; i < stages; i++) {
        cout << path[i] << (i == stages - 1 ? "\n" : " -> ");
    }

    // Output the minimum cost
    cout << "Minimum cost: " << minCost[0] << endl;
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    // Initialize graph with INF, and 0 for diagonal elements
    vector<vector<int>> graph(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }

    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges in format (from to cost), 1-based indexing:\n";
    for (int i = 0; i < edges; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u - 1][v - 1] = cost; // Convert to 0-based index
    }

    // Display the graph as an adjacency matrix
    cout << "\nGraph Representation (Adjacency Matrix):\n";
    for (const auto& row : graph) {
        for (int val : row) {
            if (val == INF)
                cout << "INF\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }

    int stages = countStages(graph);
    cout << "Number of stages: " << stages << endl;

    findMinCostPath(graph, stages);

    return 0;
}
