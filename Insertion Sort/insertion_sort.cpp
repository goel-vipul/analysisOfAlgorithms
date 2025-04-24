#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib> // For rand()

using namespace std;
using namespace std::chrono;

int main() 
{
    int currentSize = 1000; // Starting size of the array

    // Loop to gradually increase array size
    while (currentSize <= 10000) 
    {
        long long totalDuration = 0; // Accumulator for total time taken in microseconds

        // Run the test 10 times to get a stable average
        for (int trial = 1; trial <= 10; trial++) 
        {
            // Generate an array with random values
            vector<int> numbers(currentSize);
            for (int i = 0; i < currentSize; i++) 
            {
                numbers[i] = rand(); // Assign a random number
            }

            // Record time just before sorting starts
            auto startTime = high_resolution_clock::now();

            // Insertion sort implementation
            for (int i = 1; i < currentSize; i++) 
            {
                int key = numbers[i];
                int j = i - 1;

                // Shift elements to the right until correct spot for key is found
                while (j >= 0 && numbers[j] > key) 
                {
                    numbers[j + 1] = numbers[j];
                    j--;
                }
                numbers[j + 1] = key;
            }

            // Record time just after sorting finishes
            auto endTime = high_resolution_clock::now();

            // Compute how long the sorting took
            auto duration = duration_cast<microseconds>(endTime - startTime).count();
            totalDuration += duration;
        }

        // Average duration (converted from microseconds to milliseconds)
        double averageTimeInMs = totalDuration / 10.0 / 1000.0;

        // Display the result
        cout << "Array Size: " << currentSize << " | Avg Time: " << averageTimeInMs << " ms" << endl;

        // Increase array size for next test
        currentSize += 1000;
    }

    return 0;
}
