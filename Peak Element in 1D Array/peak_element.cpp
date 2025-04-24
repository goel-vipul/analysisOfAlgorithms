#include <bits/stdc++.h>
using namespace std;

// Function to find a peak element using Binary Search
int peak(int* arr, int n) {
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n - 1] > arr[n - 2]) return n - 1;

    int low = 1, high = n - 2;

    while (low <= high) {
        int mid = (low + high) / 2;

        // Check if mid is a peak
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
            return mid;

        // Move to the side that has a higher neighbor
        else if (arr[mid] > arr[mid - 1])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1; // No peak found (though this should never happen for valid input)
}

int main() {
    int arr[] = {11, 13, 20, 25, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    int index = peak(arr, n);
    cout << "Peak element is at index " << index << " with value = " << arr[index] << endl;

    return 0;
}
