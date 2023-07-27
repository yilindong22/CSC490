#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
struct timespec start, finish;

static const int total = 20;
static const  int epsilon = 10;

struct CSRMatrix {
    int* row_ptr;       // CSR row pointers
    int* col_indices;   // CSR column indices
    int nnz;            // Number of non-zero elements
};

struct Position {
    int xcoor;
    int ycoor;
};
struct Position array[total];
struct Position array2[total];

int generateRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void addElement(struct CSRMatrix* csr, int row, int col) {
    csr->col_indices[csr->nnz] = col;
    csr->nnz++;
}

void addElement2(struct CSRMatrix* csr, int row, int col) {
    csr->col_indices[csr->nnz] = col;
    csr->nnz++;
}
void* compare(){
    struct CSRMatrix csr;
    csr.row_ptr = (int*)malloc(((total/2) + 1) * sizeof(int));
    csr.col_indices = (int*)malloc((total/2) + 1 * total * sizeof(int));
    csr.nnz = 0;
    int square = epsilon * epsilon;
    

    for (int i = 0;i < total/2; i++) {
                csr.row_ptr[i + 1] = csr.nnz;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
                if (i != j) {
                    int xDiff = array[i].xcoor - array[j].xcoor;
                    int yDiff = array[i].ycoor - array[j].ycoor;
                    if ((xDiff * xDiff + yDiff * yDiff) <= square) {
                        addElement(&csr, i, j);
                    }
                }
            }
        }
    // free(csr.row_ptr);
    // free(csr.col_indices);
    printf("CSR matrix:\n");
    for (int i = 0; i <  total/2; i++) {
        printf("Row %d: ", i);
        for (int j = csr.row_ptr[i]; j < csr.row_ptr[i + 1]; j++) {
            printf("%d ", csr.col_indices[j]);
        }
        printf("\n");
    }
}
void compare2(){
    struct CSRMatrix csr2;
    csr2.row_ptr = (int*)malloc((total/2) + 1 * sizeof(int));
    csr2.col_indices = (int*)malloc((total/2) + 1 * total * sizeof(int));
    csr2.nnz = 0;
    int square2 = epsilon * epsilon;

    for (int i =total/2;i < total; i++) {
                csr2.row_ptr[i + 1] = csr2.nnz;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
                if (i != j) {
                    int xDiff2 = array2[i].xcoor - array2[j].xcoor;
                    int yDiff2 = array2[i].ycoor - array2[j].ycoor;
                    if ((xDiff2 * xDiff2 + yDiff2 * yDiff2) <= square2) {
                        addElement2(&csr2, i, j);
                    }
                }
            }
        }
    csr2.row_ptr[total] = csr2.nnz;  // Set the last row pointer
    // free(csr2.row_ptr);
    // free(csr2.col_indices);

    printf("CSR matrix:\n");
    for (int i =  total/2; i < total; i++) {
        printf("Row %d: ", i);
        for (int j = csr2.row_ptr[i]; j < csr2.row_ptr[i + 1]; j++) {
            printf("%d ", csr2.col_indices[j]);
        }
        printf("\n");
    }
 }
int main() {
    double elapsed; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    int min = 1;
    int max = 100;
    srand(10);

    for (int i = 0; i < total; i++) {
        int xcoor = generateRandomNumber(min, max);
        int ycoor = generateRandomNumber(min, max);
        array[i].xcoor = xcoor;
        array[i].ycoor = ycoor;
        array2[i].xcoor = xcoor;
        array2[i].ycoor = ycoor;
    }

    pthread_t new_thread;
    pthread_create(&new_thread,NULL,compare,NULL);
    compare2();
    pthread_join(new_thread, NULL);
    clock_gettime(CLOCK_MONOTONIC, &finish);

elapsed = (finish.tv_sec - start.tv_sec);
elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution time: %.6f seconds\n", elapsed);
    
    return 0;
}