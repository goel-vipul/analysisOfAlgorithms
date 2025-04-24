#include <iostream>
using namespace std;

// Function to find the maximum and minimum in an array using divide and conquer
pair<int, int> findMaxAndMin(int array[], int size, int start, int end) {
    // If there's only one element, it's both max and min
    if (start == end) return {array[start], array[start]};

    int mid = start + (end - start) / 2;

    // Recursively find max and min in the left and right halves
    pair<int, int> leftPair = findMaxAndMin(array, size, start, mid);
    pair<int, int> rightPair = findMaxAndMin(array, size, mid + 1, end);

    // Compare results from both halves
    int maxValue = max(leftPair.first, rightPair.first);
    int minValue = min(leftPair.second, rightPair.second);

    return {maxValue, minValue};
}

int main() {
    int numbers[] = {12, 7, 19, 5, 18, 3, 8, 11, 22, 10};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    pair<int, int> result = findMaxAndMin(numbers, length, 0, length - 1);

    cout << "Maximum element: " << result.first << endl;
    cout << "Minimum element: " << result.second << endl;

    return 0;
}
