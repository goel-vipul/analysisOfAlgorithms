#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Item; // storing (profit, weight) pairs

// This function figures out which items we picked
void backtrack(int profit, int weight, int count, vector<set<Item>> &dp, vector<int> &weights, vector<int> &values) {
    for (int i = count; i >= 1; i--) {
        int prevProfit = profit - values[i - 1];
        int prevWeight = weight - weights[i - 1];

        if (dp[i - 1].count({profit, weight})) {
            cout << "x" << i << " = 0" << endl; // we didn't take this item
        } else if (dp[i - 1].count({prevProfit, prevWeight})) {
            cout << "x" << i << " = 1" << endl; // yep, we took this one
            profit = prevProfit;
            weight = prevWeight;
        } else {
            cout << "x" << i << " = ?" << endl; // shouldn't happen
        }
    }
}

// Merges two sets and keeps only the best profits for each weight
set<Item> combine(set<Item> &a, set<Item> &b) {
    set<Item> merged = a;
    for (auto entry : b) {
        merged.insert(entry);
    }

    set<Item> filtered;
    int currentProfit = -1;
    for (auto entry : merged) {
        if (entry.first > currentProfit) {
            filtered.insert(entry); // keep this one, it's better
            currentProfit = entry.first;
        }
    }

    return filtered;
}

// The main knapsack logic
void knapsack(vector<int> &weights, vector<int> &values, int capacity) {
    int n = weights.size();
    vector<set<Item>> dp(n + 1);
    dp[0].insert({0, 0}); // starting with nothing

    for (int i = 1; i <= n; i++) {
        set<Item> newSet;
        for (auto entry : dp[i - 1]) {
            int newWeight = entry.second + weights[i - 1];
            int newProfit = entry.first + values[i - 1];
            if (newWeight <= capacity) {
                newSet.insert({newProfit, newWeight}); // try including this item
            }
        }
        dp[i] = combine(dp[i - 1], newSet); // merge with previous results
    }

    auto maxItem = dp[n].rbegin(); // pick the best profit
    int maxProfit = maxItem->first;
    int finalWeight = maxItem->second;

    cout << "Maximum profit is: " << maxProfit << endl;
    backtrack(maxProfit, finalWeight, n, dp, weights, values);
}

int main() {
    vector<int> weights = {5, 4, 6, 3};
    vector<int> values = {10, 40, 30, 50};
    int capacity = 10;

    knapsack(weights, values, capacity);
    return 0;
}
