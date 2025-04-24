#include <bits/stdc++.h>
using namespace std;

// Structure to store each item's profit and weight
struct Product {
    int value, weight;
};

// Custom comparator to sort products based on value-to-weight ratio
bool isMoreValuable(Product a, Product b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB; // Higher ratio means better value
}

// Function to calculate the maximum profit using Fractional Knapsack approach
void fillBackpack(vector<Product> items, int bagCapacity) {
    // Sort items by best value per unit weight
    sort(items.begin(), items.end(), isMoreValuable);

    double earnedProfit = 0.0;
    int filledWeight = 0;

    for (int i = 0; i < items.size(); i++) {
        // If the whole item fits, take all of it
        if (filledWeight + items[i].weight <= bagCapacity) {
            earnedProfit += items[i].value;
            filledWeight += items[i].weight;

            cout << "Picked full item: Value = " << items[i].value 
                 << ", Weight = " << items[i].weight << endl;
        } else {
            // Otherwise, take only the portion that fits
            int leftCapacity = bagCapacity - filledWeight;
            double fractionValue = items[i].value * ((double)leftCapacity / items[i].weight);
            earnedProfit += fractionValue;

            cout << "Picked part of item: Value = " << fractionValue 
                 << ", Weight = " << leftCapacity << endl;
            break; // Bag is now full
        }
    }

    cout << "Total value collected: " << earnedProfit << endl;
}

int main() {
    // Example items (value, weight)
    vector<Product> items = {{25, 18}, {24, 15}, {15, 10}};
    
    int backpackCapacity = 20;

    // Let's pack our backpack smartly
    fillBackpack(items, backpackCapacity);

    return 0;
}
