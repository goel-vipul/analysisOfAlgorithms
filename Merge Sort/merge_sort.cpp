#include <bits/stdc++.h>
using namespace std;

// Function declarations
void mergeSort(vector<long> &arr, long low, long high);
void merge(vector<long> &arr, long low, long mid, long high);

// Recursive merge sort function
void mergeSort(vector<long> &arr, long low, long high) {
    if (low >= high) return;

    long mid = low + (high - low) / 2;

    // Sort the left half
    mergeSort(arr, low, mid);
    // Sort the right half
    mergeSort(arr, mid + 1, high);

    // Merge both halves
    merge(arr, low, mid, high);
}

// Merge two sorted halves into one sorted array
void merge(vector<long> &arr, long low, long mid, long high) {
    long leftIdx = low;
    long rightIdx = mid + 1;
    vector<long> mergedArray;

    // Merge elements from both halves in sorted order
    while (leftIdx <= mid && rightIdx <= high) {
        if (arr[leftIdx] <= arr[rightIdx]) {
            mergedArray.push_back(arr[leftIdx]);
            leftIdx++;
        } else {
            mergedArray.push_back(arr[rightIdx]);
            rightIdx++;
        }
    }

    // Copy remaining elements from the left half, if any
    while (leftIdx <= mid) {
        mergedArray.push_back(arr[leftIdx]);
        leftIdx++;
    }

    // Copy remaining elements from the right half, if any
    while (rightIdx <= high) {
        mergedArray.push_back(arr[rightIdx]);
        rightIdx++;
    }

    // Copy merged elements back into the original array
    for (long i = low, idx = 0; i <= high; i++, idx++) {
        arr[i] = mergedArray[idx];
    }
}

int main() {
    long size = 10000; // Initial array size
    int iterations = 10;
    vector<double> executionTimes(iterations);

    cout << "Size, Time (seconds)" << endl;

    for (int iter = 0; iter < iterations; iter++) {
        // Generate random array of size 'size'
        vector<long> data(size);
        for (long i = 0; i < size; i++) {
            data[i] = rand() % size + 1;
        }

        // Measure execution time of merge sort
        auto startTime = chrono::high_resolution_clock::now();
        mergeSort(data, 0, size - 1);
        auto endTime = chrono::high_resolution_clock::now();

        chrono::duration<double> timeTaken = endTime - startTime;
        executionTimes[iter] = timeTaken.count();

        // Output results
        cout << size << ", " << fixed << setprecision(6) << executionTimes[iter] << endl;

        // Increase array size for next iteration
        size += 10000;
    }

    return 0;
}
