#include <bits/stdc++.h>
using namespace std;

// Function to create an odd-order magic square
void generateMagicSquare(vector<vector<int>> &grid, int size) {
    int row = 0;
    int col = size / 2; // Start from the middle of the top row

    for (int num = 1; num <= size * size; num++) {
        grid[row][col] = num; // Place the current number

        // Move one step up and one step to the right
        int nextRow = (row - 1 + size) % size;
        int nextCol = (col + 1) % size;

        // If the next cell is already filled, just move down from current cell
        if (grid[nextRow][nextCol] != 0) {
            row = (row + 1) % size;
        } else {
            row = nextRow;
            col = nextCol;
        }
    }
}

int main() {
    int n;
    cin >> n;

    if (n % 2 == 0) {
        cout << "Sorry, magic squares can only be generated for odd sizes." << endl;
        return 0;
    }

    // Create a square grid filled with zeros
    vector<vector<int>> magicSquare(n, vector<int>(n, 0));

    // Generate the magic square
    generateMagicSquare(magicSquare, n);

    // Print the magic square
    cout << "Here is your magic square of size " << n << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << magicSquare[i][j]; // Neatly format the output
        }
        cout << endl;
    }

    return 0;
}
