#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to build Minimum Spanning Tree using Prim's algorithm (near array approach)
void buildMinimumSpanningTree(int nodeCount, vector<vector<int>> &adjMatrix) {
    vector<int> closest(nodeCount, INT_MAX); // Stores the closest node in MST for each node
    vector<pair<int, int>> mstEdges;         // Stores the edges in the MST
    int totalCost = 0;

    // Step 1: Find the edge with the lowest cost to start with
    int start = -1, end = -1, lowestCost = INT_MAX;
    for (int i = 0; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            if (adjMatrix[i][j] < lowestCost) {
                lowestCost = adjMatrix[i][j];
                start = i;
                end = j;
            }
        }
    }

    // Add the initial edge to MST
    mstEdges.push_back({start, end});
    totalCost += lowestCost;

    // Step 2: Set initial closest connections
    for (int i = 0; i < nodeCount; i++) {
        if (adjMatrix[i][start] < adjMatrix[i][end]) {
            closest[i] = start;
        } else {
            closest[i] = end;
        }
    }
    closest[start] = closest[end] = -1; // Mark nodes as added to MST

    // Step 3: Continue building MST by adding (nodeCount - 2) more edges
    for (int i = 1; i < nodeCount - 1; i++) {
        int nextNode = -1, smallestLink = INT_MAX;

        // Find the next best edge to add
        for (int j = 0; j < nodeCount; j++) {
            if (closest[j] != -1 && adjMatrix[j][closest[j]] < smallestLink) {
                smallestLink = adjMatrix[j][closest[j]];
                nextNode = j;
            }
        }

        // Add the selected edge to the MST
        mstEdges.push_back({nextNode, closest[nextNode]});
        totalCost += adjMatrix[nextNode][closest[nextNode]];
        closest[nextNode] = -1; // Mark the node as added to MST

        // Update closest connections for the rest
        for (int j = 0; j < nodeCount; j++) {
            if (closest[j] != -1 && adjMatrix[j][nextNode] < adjMatrix[j][closest[j]]) {
                closest[j] = nextNode;
            }
        }
    }

    // Output the final MST and its total cost
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mstEdges) {
        cout << edge.first << " - " << edge.second << "\n";
    }
    cout << "Total cost of the MST: " << totalCost << endl;
}

int main() {
    int totalNodes = 5;
    vector<vector<int>> graph = {
        {INT_MAX, 2, INT_MAX, 6, INT_MAX},
        {2, INT_MAX, 3, 8, 5},
        {INT_MAX, 3, INT_MAX, INT_MAX, 7},
        {6, 8, INT_MAX, INT_MAX, 9},
        {INT_MAX, 5, 7, 9, INT_MAX}
    };

    buildMinimumSpanningTree(totalNodes, graph);
    return 0;
}
