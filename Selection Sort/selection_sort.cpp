#include <bits/stdc++.h>
using namespace std;

// Function to sort an array using selection sort algorithm
void selectionSort(long int numbers[], int length) {
    for (int i = 0; i < length - 1; i++) {
        int smallestIndex = i;
        
        // Find the smallest element in the remaining array
        for (int j = i + 1; j < length; j++) {
            if (numbers[j] < numbers[smallestIndex]) {
                smallestIndex = j;
            }
        }

        // Swap only if needed
        if (smallestIndex != i) {
            swap(numbers[i], numbers[smallestIndex]);
        }
    }
}

int main() {
    srand(time(0)); // Seed random number generator with current time

    int arraySize = 1000;

    // Run tests for increasing array sizes
    while (arraySize <= 25000) {
        double timeSum = 0.0;

        // Perform sorting multiple times to get a fair average
        for (int trial = 0; trial < 10; trial++) {
            long int data[arraySize];

            // Fill array with random numbers between 1 and arraySize
            for (int i = 0; i < arraySize; i++) {
                data[i] = rand() % arraySize + 1;
            }

            auto startTime = chrono::high_resolution_clock::now();
            selectionSort(data, arraySize);
            auto endTime = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = endTime - startTime;
            timeSum += elapsed.count();
        }

        double averageTime = timeSum / 10;
        cout << "Array Size: " << arraySize << ", Average Time: " << averageTime << " seconds\n";

        arraySize += 1000; // Move to next size
    }

    return 0;
}
