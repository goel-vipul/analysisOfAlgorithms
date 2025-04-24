#include <iostream>
#include <climits>

using namespace std;

const int NUM_NODES = 9;

// Helper function to find the next node with the smallest tentative distance
int getNearestUnvisited(const int distance[], const bool visited[]) {
    int minDistance = INT_MAX;
    int nearestIndex = -1;

    for (int i = 0; i < NUM_NODES; ++i) {
        if (!visited[i] && distance[i] <= minDistance) {
            minDistance = distance[i];
            nearestIndex = i;
        }
    }

    return nearestIndex;
}

// Displays the final shortest distances from the source
void displayDistances(const int distance[]) {
    cout << "Node\tDistance from Source" << endl;
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << "\t" << i << "\t\t" << distance[i] << endl;
    }
}

// Main logic for Dijkstra's algorithm
void dijkstraShortestPath(int network[NUM_NODES][NUM_NODES], int startNode) {
    int distance[NUM_NODES];  // Holds shortest distances from source
    bool visited[NUM_NODES];  // Tracks nodes that have been processed

    // Initial setup: mark all distances as infinite and none visited
    for (int i = 0; i < NUM_NODES; ++i) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[startNode] = 0; // Distance from source to itself is always 0

    // Loop through all nodes to find shortest paths
    for (int step = 0; step < NUM_NODES - 1; ++step) {
        int currentNode = getNearestUnvisited(distance, visited);
        visited[currentNode] = true;

        // Check if any neighbor can be updated
        for (int neighbor = 0; neighbor < NUM_NODES; ++neighbor) {
            if (!visited[neighbor] && network[currentNode][neighbor] &&
                distance[currentNode] != INT_MAX &&
                distance[currentNode] + network[currentNode][neighbor] < distance[neighbor]) {
                distance[neighbor] = distance[currentNode] + network[currentNode][neighbor];
            }
        }
    }

    // Show the final result
    displayDistances(distance);
}

int main() {
    int cityMap[NUM_NODES][NUM_NODES] = {
        { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
        { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
    };

    // Start the search from node 0
    dijkstraShortestPath(cityMap, 0);

    return 0;
}
