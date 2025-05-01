#include <iostream>
using namespace std;

int nodeCount, colorLimit;
int adjacencyMatrix[100][100];  // Represents the graph
int nodeColors[100];            // Stores color assigned to each node

// Checks if the current color can be safely assigned to the current node
bool isColorSafe(int currentNode, int chosenColor) {
    for (int neighbor = 1; neighbor <= nodeCount; neighbor++) {
        // If there is an edge and the neighbor has the same color
        if (adjacencyMatrix[currentNode][neighbor] && nodeColors[neighbor] == chosenColor)
            return false;
    }
    return true;
}

// Tries to assign colors to nodes using backtracking
void assignColors(int currentNode) {
    for (int color = 1; color <= colorLimit; color++) {
        if (isColorSafe(currentNode, color)) {
            nodeColors[currentNode] = color;

            if (currentNode == nodeCount) {
                // All nodes are colored, print the solution
                cout << "Coloring: ";
                for (int i = 1; i <= nodeCount; i++) {
                    cout << nodeColors[i] << " ";
                }
                cout << endl;
            } else {
                // Proceed to color the next node
                assignColors(currentNode + 1);
            }

            // Backtrack: reset the color before trying next option
            nodeColors[currentNode] = 0;
        }
    }
}

int main() {
    cout << "Enter number of nodes in the graph: ";
    cin >> nodeCount;

    cout << "Enter the number of colors available: ";
    cin >> colorLimit;

    cout << "Enter the adjacency matrix (1 if edge exists, 0 otherwise):\n";
    for (int i = 1; i <= nodeCount; i++) {
        for (int j = 1; j <= nodeCount; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0;  // No self-loop
            } else {
                cout << "Edge between node " << i << " and node " << j << ": ";
                cin >> adjacencyMatrix[i][j];
            }
        }
    }

    cout << "\nPossible valid colorings of the graph:\n";
    assignColors(1);  // Start coloring from the first node

    return 0;
}
