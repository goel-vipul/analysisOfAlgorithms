#include <iostream>
#include <climits>
using namespace std;

#define SIZE 4
#define NO_PATH INT_MAX  // Represents no direct edge between nodes

// Determines the number of stages and how many vertices each stage has
void identifyStagesAndVertices(int graph[SIZE][SIZE]) {
    int stage = 1;
    cout << "Stage " << stage << " has 1 vertex" << endl;
    stage++;

    int currentVertex = 0;

    // Traverse the graph to find out how many vertices are in each stage
    while (currentVertex != SIZE - 1) {
        int vertexCount = 0;

        // Count how many outgoing connections exist from the current vertex
        for (int nextVertex = currentVertex + 1; nextVertex < SIZE; nextVertex++) {
            if (graph[currentVertex][nextVertex] != NO_PATH) {
                vertexCount++;
            }
        }

        cout << "Stage " << stage << " has " << vertexCount << " vertices" << endl;

        // Move to the next reachable vertex to continue traversal
        for (int nextVertex = currentVertex + 1; nextVertex < SIZE; nextVertex++) {
            if (graph[currentVertex][nextVertex] != NO_PATH) {
                currentVertex = nextVertex;
                stage++;
                break;
            }
        }
    }

    cout << "Total number of stages: " << stage - 1 << endl;
}

int main() {
    // Adjacency matrix representing the multistage graph
    int graph[SIZE][SIZE] = {
        {NO_PATH, 2, 3, NO_PATH},
        {NO_PATH, NO_PATH, NO_PATH, 6},
        {NO_PATH, NO_PATH, NO_PATH, 7},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH}
    };

    identifyStagesAndVertices(graph);

    return 0;
}
