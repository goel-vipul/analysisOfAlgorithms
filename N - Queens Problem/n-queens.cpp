#include <bits/stdc++.h>
using namespace std;

int n;              // Number of queens and size of the chessboard (n x n)
int x[100];         // x[k] represents the column position of the queen in row k

// Function to check whether a queen can be placed at position (k, i)
bool place(int k, int i) {
    for (int j = 1; j < k; j++) {
        // Check for same column or diagonal attack
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return false;
    }
    return true;
}

// Recursive function to solve the N-Queens problem
void NQueen(int k) {
    for (int i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i; // Place the queen at column i in row k
            if (k == n) {
                // All queens placed successfully - print the solution
                for (int j = 1; j <= n; j++)
                    cout << x[j] << " ";
                cout << endl;
            } else {
                NQueen(k + 1); // Recur to place the next queen
            }
        }
    }
}

int main() {
    cout << "Enter number of queens: ";
    cin >> n;
    cout << "Solutions to the " << n << "-Queens problem:\n";
    NQueen(1); // Start placing from the first row
    return 0;
}
