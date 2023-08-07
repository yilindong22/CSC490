#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

struct timespec start, finish;

static const int total = 100000;
static const  int epsilon = 10;

struct CSRMatrix {
    int* row_ptr;       // CSR row pointers
    int* col_indices;   // CSR column indices
    int nnz;            // Number of non-zero elements
};

void construct_CSR( struct CSRMatrix * csr, int matrix_size )
{
     csr->row_ptr = (int*)malloc((matrix_size + 1) * sizeof(int));
    csr->col_indices = (int*)malloc(matrix_size * matrix_size*2 * sizeof(int));
    csr->nnz = 0;
    if( csr->row_ptr == NULL || csr->col_indices == NULL )
    {
        printf("Allocation error!\n");
    }
}

void construct_CSR2( struct CSRMatrix * csr, int matrix_size )
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
// void print_CSR( struct CSRMatrix * csr )
// {
//     printf("CSR matrix:\n");
//     for (int i = total/2; i < total; i++) {
//         for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
//             if(csr->col_indices[j] == 7) {
//                 printf("%d ", csr->col_indices[j]);
//             }
//         }
//     }
// }

//print the total array
void print_CSR2( struct CSRMatrix * csr )
{
    for (int i = 0; i < total; i++) {
                if (csr->row_ptr[i] != csr->row_ptr[i + 1]) {
        printf("Row %d: ", i);
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            printf("%d ", csr->col_indices[j]);
        }
        printf("\n");
    }
    }
}

struct Position {
    int xcoor;
    int ycoor;
};



struct Position array[total];


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
    for (int i = 0;i < total/5; i++) {
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

    for (int i =total/5;i < 2*total/5; i++) {
        *cur_row++ = num_matches;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
            if (i != j) {
                int xDiff2 = array[i].xcoor - array[j].xcoor;
                int yDiff2 = array[i].ycoor - array[j].ycoor;
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

void* compare3( void * output_matrix ){
    struct CSRMatrix *csr3 = (struct CSRMatrix *) output_matrix;

    int num_matches = 0;
    int *cur_row = csr3->row_ptr;
    int *cur_neighbour = csr3->col_indices;

    int square = epsilon * epsilon;
    
    for (int i = 2*total/5;i < (3*total)/5; i++) {
        *cur_row++ = num_matches;  // Initialize row pointer for the current row
        for (int j = 0;j < total; j++) {
            if (i != j) {
                int xDiff = array[i].xcoor - array[j].xcoor;
                int yDiff = array[i].ycoor - array[j].ycoor;
                if ((xDiff * xDiff + yDiff * yDiff) <= square) {
                    ++num_matches;
                    *cur_neighbour++ = j;                }
            }
        }
    }
    // Set the last row pointer
    *cur_row = num_matches;
    csr3->nnz = num_matches;
    // print_CSR(csr);
    pthread_exit(NULL);
}
void* compare4( void * output_matrix ){
    struct CSRMatrix *csr4 = (struct CSRMatrix *) output_matrix;

    int num_matches = 0;
    int *cur_row = csr4->row_ptr;
    int *cur_neighbour = csr4->col_indices;

    int square = epsilon * epsilon;
    
    for (int i = (3*total)/5;i < (4*total)/5; i++) {
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
    csr4->nnz = num_matches;
    // print_CSR2(csr4);
    pthread_exit(NULL);
}
void* compare5( void * output_matrix ){
    struct CSRMatrix *csr = (struct CSRMatrix *) output_matrix;

    int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;

    int square = epsilon * epsilon;
    for (int i = (4*total)/5;i < total; i++) {
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
   // print_CSR(csr);
    pthread_exit(NULL);
}

void* cluster(void * output_matrix, struct CSRMatrix * merged){
    struct CSRMatrix *csr = (struct CSRMatrix *) output_matrix;
    int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;
    int stored[total];
    int destLen = 0;
    bool* exists = (bool*)calloc(total + 1, sizeof(bool));
    if (exists == NULL) {
        printf("Memory allocation failed\n");
        return(0);
    }

    for (int i = 0; i < total; i++) {
        *cur_row++ = num_matches;  // Initialize row pointer for the current row
        if (merged->row_ptr[i] != merged->row_ptr[i + 1] &&(!exists[i])) {
            exists[i] = true; //
            stored[destLen++] = i;
            ++num_matches;
            *cur_neighbour++ = i;
            for (int j = merged->row_ptr[i]; j < merged->row_ptr[i + 1]; j++) {
                if (!exists[merged->col_indices[j]]) {
                    ++num_matches;
                    *cur_neighbour++ = merged->col_indices[j];
                    exists[merged->col_indices[j]] = true; //
                    stored[destLen++] =merged->col_indices[j];
                }
            }
        }
    }
    // Set the last row pointer
    *cur_row = num_matches;
    csr->nnz = num_matches;
    // print_CSR2(&csr);
    // for (int i = 0; i < destLen; i++) {
    //     printf("Row %d: ", i);
    //     for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
    //         printf("%d ", csr->col_indices[j]);
    //     }
    //     printf("\n");
    // }
    }


int main() {
    double elapsed; 

    clock_gettime(CLOCK_MONOTONIC, &start);    
    struct CSRMatrix csr1, csr2, csr3,csr4,csr_merged,csr5;
    pthread_t new_thread, new_thread2,new_thread3,new_thread4,new_thread5;
    int min = 1;
    int max = 100;
    srand(10);
    int t = total/5;
    int t2 = 2*total/5;
    int t3 = total*3/5;
    int t4 = 4*total/5;
    for (int i = 0; i < total; i++) {
        int xcoor = generateRandomNumber(min, max);
        int ycoor = generateRandomNumber(min, max);
        array[i].xcoor = xcoor;
        array[i].ycoor = ycoor;

    }

    construct_CSR( &csr1, total/5 );
    construct_CSR( &csr2, total/5 );
    construct_CSR( &csr3, total/5 );
    construct_CSR( &csr4, total/5 );
    construct_CSR( &csr5, total/5 );

    construct_CSR2( &csr_merged, total );



#ifndef NMULTITHREAD
    pthread_create(&new_thread,NULL,compare, (void *) &csr1);
    pthread_create(&new_thread2,NULL,compare2, (void *) &csr2);
    pthread_create(&new_thread3,NULL,compare3, (void *) &csr3);
    pthread_create(&new_thread4,NULL,compare4, (void *) &csr4);
    pthread_create(&new_thread5,NULL,compare5, (void *) &csr5);
    pthread_join(new_thread, NULL);
    pthread_join(new_thread2, NULL);
    pthread_join(new_thread3, NULL);
    pthread_join(new_thread4, NULL);
    pthread_join(new_thread5, NULL);

#else
    pthread_create(&new_thread,NULL,compare, (void *) &csr1);
    pthread_join(new_thread, NULL);
    pthread_create(&new_thread2,NULL,compare2, (void *) &csr2);
    pthread_join(new_thread2, NULL);
    pthread_create(&new_thread3,NULL,compare3, (void *) &csr3);
    pthread_join(new_threa3d, NULL);
    pthread_create(&new_thread4,NULL,compare4, (void *) &csr4);
    pthread_join(new_thread4, NULL);
      pthread_create(&new_thread5,NULL,compare5, (void *) &csr5);
    pthread_join(new_thread5, NULL);
#endif


csr_merged.row_ptr[0] = 0; // Initialize the first row pointer

    // Copy data from csr1 to csr_merged
    memcpy(csr_merged.col_indices, csr1.col_indices, csr1.nnz * sizeof(int));
    for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i] = csr1.row_ptr[i];
    }
    // Update row pointers and copy data from csr2 to csr_merged
    for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i + t] = csr2.row_ptr[i] + csr1.nnz;
    }

    memcpy(csr_merged.col_indices + csr1.nnz, csr2.col_indices, csr2.nnz * sizeof(int));
    // Set the total nnz for csr_merged
    csr_merged.nnz = csr1.nnz + csr2.nnz;
    // Print the merged CSR matrix
     for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i + t2] = csr3.row_ptr[i] + csr_merged.nnz;
    }

    memcpy(csr_merged.col_indices + csr_merged.nnz, csr3.col_indices, csr3.nnz * sizeof(int));
    csr_merged.nnz += csr3.nnz;

    // Update row pointers and copy data from csr4 to csr_merged
    for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i + t3] = csr4.row_ptr[i] + csr_merged.nnz;
    }

    memcpy(csr_merged.col_indices + csr_merged.nnz, csr4.col_indices, csr4.nnz * sizeof(int));
    csr_merged.nnz += csr4.nnz;

    for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i + t3] = csr4.row_ptr[i] + csr_merged.nnz;
    }

    memcpy(csr_merged.col_indices + csr_merged.nnz, csr4.col_indices, csr4.nnz * sizeof(int));
    csr_merged.nnz += csr4.nnz;

    for (int i = 0; i <= total / 5; i++) {
        csr_merged.row_ptr[i + t4] = csr5.row_ptr[i] + csr_merged.nnz;
    }

    memcpy(csr_merged.col_indices + csr_merged.nnz, csr5.col_indices, csr5.nnz * sizeof(int));
    csr_merged.nnz += csr5.nnz;
   // destruct_CSR(&csr1);
    //destruct_CSR(&csr2);


    struct CSRMatrix clus;
    construct_CSR( &clus, total );
    cluster((void *) &clus,&csr_merged);

clock_gettime(CLOCK_MONOTONIC, &finish);
elapsed = (finish.tv_sec - start.tv_sec);
elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution time: %.6f seconds\n", elapsed);
    // clean up

    // print_CSR2(&csr_merged);

    return 0;
}