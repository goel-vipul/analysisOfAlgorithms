#include <iostream>
#include <vector>

using namespace std;

// Define a matrix as a 2D vector of integers
typedef vector<vector<int>> Matrix;

// Adds two matrices and returns the result
Matrix addMatrices(const Matrix &mat1, const Matrix &mat2, int size) {
    Matrix sum(size, vector<int>(size, 0));
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            sum[row][col] = mat1[row][col] + mat2[row][col];
    return sum;
}

// Subtracts the second matrix from the first
Matrix subtractMatrices(const Matrix &mat1, const Matrix &mat2, int size) {
    Matrix diff(size, vector<int>(size, 0));
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            diff[row][col] = mat1[row][col] - mat2[row][col];
    return diff;
}

// Performs matrix multiplication using Strassen’s algorithm
Matrix strassenMultiply(Matrix A, Matrix B, int size) {
    // Base case for recursion
    if (size == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = size / 2;
    Matrix A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize));
    Matrix A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize));
    Matrix B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize));
    Matrix B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));

    // Splitting matrices into 4 submatrices each
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Applying Strassen’s formula for multiplication
    Matrix P1 = strassenMultiply(A11, subtractMatrices(B12, B22, newSize), newSize);
    Matrix P2 = strassenMultiply(addMatrices(A11, A12, newSize), B22, newSize);
    Matrix P3 = strassenMultiply(addMatrices(A21, A22, newSize), B11, newSize);
    Matrix P4 = strassenMultiply(A22, subtractMatrices(B21, B11, newSize), newSize);
    Matrix P5 = strassenMultiply(addMatrices(A11, A22, newSize), addMatrices(B11, B22, newSize), newSize);
    Matrix P6 = strassenMultiply(subtractMatrices(A12, A22, newSize), addMatrices(B21, B22, newSize), newSize);
    Matrix P7 = strassenMultiply(subtractMatrices(A11, A21, newSize), addMatrices(B11, B12, newSize), newSize);

    // Calculating the submatrices of the result
    Matrix C11 = addMatrices(subtractMatrices(addMatrices(P5, P4, newSize), P2, newSize), P6, newSize);
    Matrix C12 = addMatrices(P1, P2, newSize);
    Matrix C21 = addMatrices(P3, P4, newSize);
    Matrix C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1, newSize), P3, newSize), P7, newSize);

    // Combining submatrices into one final matrix
    Matrix result(size, vector<int>(size, 0));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            result[i][j] = C11[i][j];
            result[i][j + newSize] = C12[i][j];
            result[i + newSize][j] = C21[i][j];
            result[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return result;
}

// Prints the elements of a matrix in a neat format
void displayMatrix(const Matrix &matrix) {
    for (const auto &row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main() {
    int dimension = 4;  // Make sure the size is a power of 2
    Matrix matrixA = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    Matrix matrixB = {
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}
    };

    cout << "Matrix A:\n";
    displayMatrix(matrixA);
    cout << "\nMatrix B:\n";
    displayMatrix(matrixB);

    Matrix product = strassenMultiply(matrixA, matrixB, dimension);

    cout << "\nProduct of A and B:\n";
    displayMatrix(product);

    return 0;
}
