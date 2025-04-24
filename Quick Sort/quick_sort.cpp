#include <bits/stdc++.h>
using namespace std;

// Function to partition the array using Lomuto partition scheme
int partitionArray(long int data[], int start, int end) {
    long int pivot = data[start];
    int left = start;
    int right = end;

    // Move elements around the pivot
    while (left < right) {
        while (data[left] <= pivot && left <= end - 1) {
            left++;
        }

        while (data[right] > pivot && right >= start + 1) {
            right--;
        }

        if (left < right) {
            swap(data[left], data[right]);
        }
    }

    // Place pivot in its correct position
    swap(data[start], data[right]);
    return right;
}

// Recursive quick sort function
void quickSort(long int data[], int start, int end) {
    if (start < end) {
        int pivotIndex = partitionArray(data, start, end);
        quickSort(data, start, pivotIndex - 1);
        quickSort(data, pivotIndex + 1, end);
    }
}

int main() {
    srand(time(0)); // Initialize random seed

    int size = 1000;
    
    // Benchmarking quick sort for increasing input sizes
    while (size <= 25000) {
        double cumulativeTime = 0.0;

        // Run sorting 10 times for each size and average the time
        for (int trial = 0; trial < 10; trial++) {
            long int numbers[size];

            // Fill the array with random numbers in range [1, size]
            for (int i = 0; i < size; i++) {
                numbers[i] = rand() % size + 1;
            }

            auto startTime = chrono::high_resolution_clock::now();
            quickSort(numbers, 0, size - 1);
            auto endTime = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsedTime = endTime - startTime;
            cumulativeTime += elapsedTime.count();
        }

        double averageTime = cumulativeTime / 10;
        cout << "Array size: " << size << ", Average time: " << averageTime << " seconds\n";

        size += 1000; // Step to the next size
    }

    return 0;
}
