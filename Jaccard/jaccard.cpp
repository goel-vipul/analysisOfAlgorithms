#include <bits/stdc++.h>
using namespace std;

// Function to compute the Jaccard Similarity Coefficient
void jaccardSimilarity(const vector<int>& arr1, const vector<int>& arr2) {
    // Use sets to remove duplicates and work with unique elements
    unordered_set<int> set1(arr1.begin(), arr1.end());
    unordered_set<int> set2(arr2.begin(), arr2.end());

    int intersectionCount = 0;
    unordered_set<int> unionSet = set1;

    // Count elements that are present in both sets
    for (int num : set2) {
        if (set1.count(num)) {
            intersectionCount++;
        }
        unionSet.insert(num); // Add all elements to the union set
    }

    int unionCount = unionSet.size();

    // Compute and display the Jaccard coefficient
    double jaccardIndex = static_cast<double>(intersectionCount) / unionCount;
    cout << "Jaccard Coefficient of Similarity = " << jaccardIndex << endl;
}

int main() {
    vector<int> arr1 = {0, 1, 2, 5, 6};
    vector<int> arr2 = {0, 2, 3, 4, 5, 7, 9};
    
    jaccardSimilarity(arr1, arr2);
    return 0;
}
