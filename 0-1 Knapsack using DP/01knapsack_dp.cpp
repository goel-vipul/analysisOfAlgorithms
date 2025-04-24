#include <bits/stdc++.h>
using namespace std;

// Standard DP-based knapsack function
int solveKnapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0)); // dp[i][w] = max value using first i items within weight w

    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                // Try taking or skipping the item, choose max
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Can't take the item, just copy the value above
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Trace back to find what items we picked
    int w = capacity;
    vector<int> pickedItems;

    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            pickedItems.push_back(i - 1); // yep, this one was included
            w -= weights[i - 1]; // adjust remaining capacity
        }
    }

    // Output results
    cout << "Maximum profit: " << dp[n][capacity] << endl;
    cout << "Items picked (1-based index): ";
    for (int i : pickedItems) {
        cout << i + 1 << " ";
    }
    cout << endl;

    return dp[n][capacity];
}

int main() {
    vector<int> weights = {5, 4, 6, 3};
    vector<int> profits = {10, 40, 30, 50};
    int capacity = 10;

    solveKnapsack(weights, profits, capacity);
    return 0;
}
