#include <iostream>
using namespace std;

// recursive binary search
bool searchBinary(int arr[], int key, int left, int right) {
    if (left > right) return false; // key not found

    int mid = left + (right - left) / 2;

    if (arr[mid] == key) return true; // key found

    if (key < arr[mid]) {
        return searchBinary(arr, key, left, mid - 1); // look in left half
    } else {
        return searchBinary(arr, key, mid + 1, right); // look in right half
    }
}

int main() {
    int data[] = {2, 3, 4, 10, 40};
    int size = sizeof(data) / sizeof(data[0]);
    int target = 10;

    bool found = searchBinary(data, target, 0, size - 1);

    if (found)
        cout << "Element found" << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
