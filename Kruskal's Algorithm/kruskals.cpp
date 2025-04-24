#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union (DSU) structure to manage sets of connected nodes
class DisjointSet {
    vector<int> parent;

public:
    // Constructor: initializes each node as its own parent (with -1)
    DisjointSet(int size) {
        parent.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = -1;
        }
    }

    // Find function with path compression
    int findRoot(int node) {
        if (parent[node] < 0) return node;
        return parent[node] = findRoot(parent[node]);
    }

    // Union by size: attach the smaller tree to the larger one
    bool connect(int a, int b) {
        int rootA = findRoot(a);
        int rootB = findRoot(b);

        if (rootA == rootB) return false; // Already in the same set

        // Attach smaller set to larger one (more negative value means larger)
        if (parent[rootA] < parent[rootB]) {
            parent[rootA] += parent[rootB];
            parent[rootB] = rootA;
        } else {
            parent[rootB] += parent[rootA];
            parent[rootA] = rootB;
        }

        return true;
    }
};

// Custom comparator for min-heap based on edge weights
struct EdgeCompare {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[0] > b[0]; // Smaller weight has higher priority
    }
};

// Function to find Minimum Spanning Tree using Kruskal’s Algorithm
void findMST(int totalNodes, vector<vector<int>>& connections) {
    // Use min-heap to pick the smallest edge each time
    priority_queue<vector<int>, vector<vector<int>>, EdgeCompare> edgeHeap(connections.begin(), connections.end());

    DisjointSet ds(totalNodes);
    int totalCost = 0;
    int edgeCount = 0;

    while (!edgeHeap.empty() && edgeCount < totalNodes - 1) {
        auto edge = edgeHeap.top();
        edgeHeap.pop();

        int weight = edge[0];
        int node1 = edge[1];
        int node2 = edge[2];

        // If the nodes are not already connected, take this edge
        if (ds.connect(node1, node2)) {
            totalCost += weight;
            edgeCount++;

            cout << "Connected: " << node1 << " - " << node2 << " | Cost: " << weight << endl;
        }
    }

    if (edgeCount == totalNodes - 1)
        cout << "Total cost of MST: " << totalCost << endl;
    else
        cout << "A complete MST is not possible with the given edges." << endl;
}

int main() {
    int nodes = 5; // Total number of nodes in the graph
    vector<vector<int>> edgeList = {
        {2, 0, 1}, {3, 1, 2}, {7, 2, 4}, {5, 1, 4}, 
        {9, 3, 4}, {6, 0, 3}, {8, 1, 3}
    };

    findMST(nodes, edgeList);

    return 0;
}
