#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

struct timespec start, finish;

static const int total = 100000;

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
     double elapsed; 
    clock_gettime(CLOCK_MONOTONIC, &start);
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

    int square = epsilon * epsilon;
    for (int i = 0;i < total; i++) {
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
    
    csr.row_ptr[total] = csr.nnz;  // Set the last row pointer
    clock_gettime(CLOCK_MONOTONIC, &finish);


    printf("%d",csr.nnz);
    // Print the CSR matrix for debugging purposes
    printf("CSR matrix:\n");
    
    // for (int i = 0; i < total; i++) {
    //     printf("Row %d: ", i);
    //     for (int j = csr.row_ptr[i]; j < csr.row_ptr[i + 1]; j++) {
    //         printf("%d ", csr.col_indices[j]);
    //     }
    //     printf("\n");
    // }

    free(csr.row_ptr);
    free(csr.col_indices);
elapsed = (finish.tv_sec - start.tv_sec);
elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution time: %.6f seconds\n", elapsed);
    return 0;
}