#include <bits/stdc++.h>
using namespace std;

// Bubble sort function for sorting the array
void bubbleSort(long int* data, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

int main() {
    srand(time(0)); // set random seed for different results on each run

    int size = 1000;

    while (size <= 25000) {
        double totalTime = 0.0;

        // Running 10 trials for each size to get average time
        for (int trial = 1; trial <= 10; trial++) {
            long int arr[size];

            // Fill the array with random numbers
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % size + 1;
            }

            auto start = chrono::high_resolution_clock::now();
            bubbleSort(arr, size);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration = end - start;
            totalTime += duration.count();
        }

        double avgTime = totalTime / 10;
        cout << "Size: " << size << ", Time: " << avgTime << " seconds" << endl;

        size += 1000; // increase the size step by step
    }

    return 0;
}
