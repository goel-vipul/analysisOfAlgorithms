#include <bits/stdc++.h>
using namespace std;

// Recursive function to print optimal parenthesization
void printOptimalOrder(vector<vector<int>> &splitMatrix, int start, int end) {
    if (start == end) {
        cout << "A" << start;  // Single matrix
    } else {
        cout << "(";
        printOptimalOrder(splitMatrix, start, splitMatrix[start][end]);
        printOptimalOrder(splitMatrix, splitMatrix[start][end] + 1, end);
        cout << ")";
    }
}

// Function to calculate minimum cost for matrix chain multiplication
void findMinimumMultiplicationCost(vector<int> &dimensions) {
    int numMatrices = dimensions.size() - 1;

    // m[i][j] will store the minimum cost of multiplying matrix i to j
    vector<vector<int>> cost(numMatrices, vector<int>(numMatrices, 0));
    // s[i][j] will store the index at which the optimal split occurs
    vector<vector<int>> split(numMatrices, vector<int>(numMatrices, 0));

    // l is the length of the matrix chain
    for (int chainLength = 2; chainLength <= numMatrices; chainLength++) {
        for (int i = 0; i <= numMatrices - chainLength; i++) {
            int j = i + chainLength - 1;
            cost[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int currentCost = cost[i][k] + cost[k + 1][j] +
                                  dimensions[i] * dimensions[k + 1] * dimensions[j + 1];

                if (currentCost < cost[i][j]) {
                    cost[i][j] = currentCost;
                    split[i][j] = k;  // Remember where to split
                }
            }
        }
    }

    cout << "Minimum number of scalar multiplications: " << cost[0][numMatrices - 1] << endl;
    cout << "Optimal parenthesization: ";
    printOptimalOrder(split, 0, numMatrices - 1);
    cout << endl;
}

int main() {
    vector<int> matrixDimensions = {5, 10, 15, 20, 25, 30};

    findMinimumMultiplicationCost(matrixDimensions);

    return 0;
}
