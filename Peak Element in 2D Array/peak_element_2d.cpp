#include <bits/stdc++.h>
using namespace std;

// Helper function to find the row index of the largest element in a given column
int getRowWithMaxInColumn(const vector<vector<int>>& matrix, int totalRows, int columnIndex) {
    int maxVal = -1;
    int rowIndexWithMax = -1;

    for (int row = 0; row < totalRows; row++) {
        if (matrix[row][columnIndex] > maxVal) {
            maxVal = matrix[row][columnIndex];
            rowIndexWithMax = row;
        }
    }
    return rowIndexWithMax;
}

// Function to find a peak element in a 2D matrix
vector<int> findPeakElement(const vector<vector<int>>& matrix) {
    int rowCount = matrix.size();
    int colCount = matrix[0].size();
    int left = 0;
    int right = colCount - 1;

    while (left <= right) {
        int midCol = (left + right) / 2;
        int maxRow = getRowWithMaxInColumn(matrix, rowCount, midCol);

        // Check if the current element is a peak
        bool isLeftSmaller = (midCol == 0 || matrix[maxRow][midCol - 1] < matrix[maxRow][midCol]);
        bool isRightSmaller = (midCol == colCount - 1 || matrix[maxRow][midCol] > matrix[maxRow][midCol + 1]);

        if (isLeftSmaller && isRightSmaller) {
            return {maxRow, midCol};
        }

        // If left neighbor is bigger, move to the left half
        if (midCol > 0 && matrix[maxRow][midCol - 1] > matrix[maxRow][midCol]) {
            right = midCol - 1;
        } else {
            // Else move to the right half
            left = midCol + 1;
        }
    }

    return {-1, -1}; // In case no peak is found (shouldn't happen with valid input)
}

int main() {
    vector<vector<int>> matrix = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };

    vector<int> peakPosition = findPeakElement(matrix);

    if (peakPosition[0] != -1) {
        cout << "Peak element is: " << matrix[peakPosition[0]][peakPosition[1]] << endl;
    } else {
        cout << "No peak element found." << endl;
    }

    return 0;
}
