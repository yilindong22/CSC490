#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

static const int total = 100000;
static const  int epsilon = 0;

struct CSRMatrix {
    int* row_ptr;       // CSR row pointers
    int* col_indices;   // CSR column indices
    int nnz;            // Number of non-zero elements
};

void construct_CSR( struct CSRMatrix * csr, int matrix_size )
{
    csr->row_ptr = (int*)malloc((matrix_size + 1) * sizeof(int));
    csr->col_indices = (int*)malloc(matrix_size * matrix_size * sizeof(int));
    csr->nnz = 0;

    if( csr->row_ptr == NULL || csr->col_indices == NULL )
    {
        printf("Allocation error!\n");
    }
}

void destruct_CSR( struct CSRMatrix * csr )
{
    free( csr->row_ptr );
    free( csr->col_indices );
}

// random print method to use the output for something
// doesn't print whole matrix
void print_CSR( struct CSRMatrix * csr )
{
    printf("CSR matrix:\n");
    for (int i = total/2; i < total; i++) {
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            if(csr->col_indices[j] == 7) {
                printf("%d ", csr->col_indices[j]);
            }
        }
    }
}


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
    //csr->col_indices[csr->nnz] = col;
    csr->nnz++;
}

void addElement2(struct CSRMatrix* csr, int row, int col) {
    //csr->col_indices[csr->nnz] = col;
    csr->nnz++;
}

void* compare( void * output_matrix ){
    struct CSRMatrix *csr = (struct CSRMatrix *) output_matrix;

    int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;

    int square = epsilon * epsilon;
    
    for (int i = 0;i < total/2; i++) {
        *cur_row++ = num_matches;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
            if (i != j) {
                int xDiff = array[i].xcoor - array[j].xcoor;
                int yDiff = array[i].ycoor - array[j].ycoor;
                if ((xDiff * xDiff + yDiff * yDiff) <= square) {
                    ++num_matches;
                    *cur_neighbour++ = j;
                }
            }
        }
    }
    // Set the last row pointer
    *cur_row = num_matches;
    csr->nnz = num_matches;

    pthread_exit(NULL);
}

void* compare2( void * output_matrix ){
    struct CSRMatrix *csr2 = (struct CSRMatrix *) output_matrix;

    int num_matches = 0;
    int *cur_row = csr2->row_ptr;
    int *cur_neighbour = csr2->col_indices;

    int square2 = epsilon * epsilon;

    for (int i =total/2;i < total; i++) {
        *cur_row++ = num_matches;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
            if (i != j) {
                int xDiff2 = array2[i].xcoor - array2[j].xcoor;
                int yDiff2 = array2[i].ycoor - array2[j].ycoor;
                if ((xDiff2 * xDiff2 + yDiff2 * yDiff2) <= square2) {
                    ++num_matches;
                    *cur_neighbour++ = j;
                }
            }
        }
    }
    // Set the last row pointer
    *cur_row = num_matches;
    csr2->nnz = num_matches;

    pthread_exit(NULL);
}


int main() {
    struct CSRMatrix csr1, csr2;
    pthread_t new_thread, new_thread2;
    int min = 100;
    int max = 10000;
    srand(10);

    for (int i = 0; i < total; i++) {
        int xcoor = generateRandomNumber(min, max);
        int ycoor = generateRandomNumber(min, max);
        array[i].xcoor = xcoor;
        array[i].ycoor = ycoor;
        array2[i].xcoor = xcoor;
        array2[i].ycoor = ycoor;
    }

    construct_CSR( &csr1, total );
    construct_CSR( &csr2, total );

    clock_t start = clock();

#ifndef NMULTITHREAD
    pthread_create(&new_thread,NULL,compare, (void *) &csr1);
    pthread_create(&new_thread2,NULL,compare2, (void *) &csr2);
    pthread_join(new_thread, NULL);
    pthread_join(new_thread2, NULL);
#else
    pthread_create(&new_thread,NULL,compare, (void *) &csr1);
    pthread_join(new_thread, NULL);
    pthread_create(&new_thread2,NULL,compare2, (void *) &csr2);
    pthread_join(new_thread2, NULL);
#endif

    clock_t end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", executionTime);

    // clean up
    destruct_CSR(&csr1);
    destruct_CSR(&csr2);
    
    return 0;
}