#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const int total = 20;

struct CSRMatrix {
    int* row_ptr;       // CSR row pointers
    int* col_indices;   // CSR column indices
    int nnz;            // Number of non-zero elements
};

struct Position {
    int xcoor;
    int ycoor;
};

int generateRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void addElement(struct CSRMatrix* csr, int row, int col) {
    csr->col_indices[csr->nnz] = col;
    csr->nnz++;
}

int main() {
    int min = 1;
    int max = 100;
    int epsilon = 10;
    struct Position array[total];
    srand(10);

    for (int i = 0; i < total; i++) {
        array[i].xcoor = generateRandomNumber(min, max);
        array[i].ycoor = generateRandomNumber(min, max);
    }

    struct CSRMatrix csr;
    csr.row_ptr = (int*)malloc((total + 1) * sizeof(int));
    csr.col_indices = (int*)malloc(total * total * sizeof(int));
    csr.nnz = 0;

    clock_t start = clock();
    int B = 10;
    int square = epsilon * epsilon;
    for (int t = 0;t < total; t+=B) {
       for (int i = t;i < t+B; i++) {
                csr.row_ptr[i + 1] = csr.nnz;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
                if (i != j) {
                    int xDiff = array[i].xcoor - array[j].xcoor;
                    int yDiff = array[i].ycoor - array[j].ycoor;
                    if ((xDiff * xDiff + yDiff * yDiff) <= square) {
                        addElement(&csr, i, j);
                         csr.row_ptr[i + 1] = csr.nnz;  // Initialize row pointer for the current row


                    }
                }
            }
        }
    }
    csr.row_ptr[total] = csr.nnz;  // Set the last row pointer

    clock_t end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", executionTime);

    // Print the CSR matrix for debugging purposes
    printf("CSR matrix:\n");
    for (int i = 0; i < total; i++) {
        printf("Row %d: ", i);
        for (int j = csr.row_ptr[i]; j < csr.row_ptr[i + 1]; j++) {
            printf("%d ", csr.col_indices[j]);
        }
        printf("\n");
    }

    free(csr.row_ptr);
    free(csr.col_indices);

    return 0;
}
