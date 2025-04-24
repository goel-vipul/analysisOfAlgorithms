#include <bits/stdc++.h>
using namespace std;

// Partition the array based on the pivot (chosen as the first element)
int partitionArray(long int arr[], long int left, long int right) {
    long int pivot = arr[left];
    long int i = left + 1;
    long int j = right;

    while (i <= j) {
        while (i <= j && arr[i] <= pivot) {
            i++;
        }
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[left], arr[j]);
    return j; // Return the final position of the pivot
}

// Iterative implementation of QuickSort using a stack
void quickSortIterative(long int arr[], int left, int right) {
    stack<int> bounds;

    do {
        while (left < right) {
            int pivotIndex = partitionArray(arr, left, right);

            // Push the larger subarray on stack to reduce stack depth
            if ((pivotIndex - left) > (right - pivotIndex)) {
                bounds.push(left);
                bounds.push(pivotIndex - 1);
                left = pivotIndex + 1;
            } else {
                bounds.push(pivotIndex + 1);
                bounds.push(right);
                right = pivotIndex - 1;
            }
        }

        if (bounds.empty()) break;

        right = bounds.top(); bounds.pop();
        left = bounds.top(); bounds.pop();
    } while (true);
}

// Check if the array is sorted in ascending order
bool checkIfSorted(long int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

int main() {
    srand(time(0)); // Seed the random number generator

    int arraySize = 1000;

    while (arraySize <= 10000) {
        double totalTime = 0.0;

        // Run sorting 10 times to get a good average
        for (int trial = 1; trial <= 10; trial++) {
            long int arr[arraySize];

            // Fill the array with random numbers
            for (int i = 0; i < arraySize; i++) {
                arr[i] = rand() % arraySize + 1;
            }

            auto startTime = chrono::high_resolution_clock::now();
            quickSortIterative(arr, 0, arraySize - 1);
            auto endTime = chrono::high_resolution_clock::now();

            chrono::duration<double> runTime = endTime - startTime;
            totalTime += runTime.count();

            // Make sure the array was sorted properly
            if (!checkIfSorted(arr, arraySize)) {
                cout << "Sort failed for size " << arraySize << endl;
                return 1;
            }
        }

        // Show average time taken for sorting
        double averageTime = totalTime / 10.0;
        cout << "Size: " << arraySize << " | Avg Time: " << averageTime << " seconds" << endl;

        arraySize += 1000;
    }

    return 0;
}
