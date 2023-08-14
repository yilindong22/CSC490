#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

struct timespec start, finish;

static const int total = 10000;
static const  int epsilon = 10;

struct CSRMatrix {
    int* row_ptr;       // CSR row pointers
    int* col_indices;   // CSR column indices
    int nnz;            // Number of non-zero elements
};
struct GridArgs {
    struct CSRMatrix* output_matrix;
    struct CSRMatrix* merged;
    int* grid;
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

void* grid_p(void * args){
    struct GridArgs* gridArgs = (struct GridArgs*) args;
    struct CSRMatrix* csr = gridArgs->output_matrix;
    struct CSRMatrix* merged = gridArgs->merged;
    int* grid = gridArgs->grid;   
     int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;
    bool* exists = (bool*)calloc(total + 1, sizeof(bool));
    if (exists == NULL) {
        printf("Memory allocation failed\n");
        return(0);
    }
    int x = 0;
    for(int i = 0; i <= (total/2)-1; i ++){
        if ( (!exists[grid[i]]) &&(grid[i] != grid[i + 1] )) {
                    *cur_row++ = num_matches;  // Initialize row pointer for the current row

            exists[grid[i]] = true; //
            ++num_matches;
            *cur_neighbour++ = grid[i];
            for (int j = merged->row_ptr[grid[i]]; j < merged->row_ptr[grid[i] + 1]; j++) {
                if (!exists[merged->col_indices[j]]) {
                    ++num_matches;
                    *cur_neighbour++ = merged->col_indices[j];
                    exists[merged->col_indices[j]] = true; //

                }
            }
        }
       
    }
    *cur_row = num_matches;
//  for (int i = 0; i < total/2; i++) {
//         if ( (grid[i] != grid[i + 1])
//          ) {
//         printf("Row %d: ",i);
//         for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
//             printf("%d ", csr->col_indices[j]);
//         }
//         printf("\n");
//      }
//     }

    
}

void* grid_p2(void * args){
    struct GridArgs* gridArgs = (struct GridArgs*) args;
    struct CSRMatrix* csr = gridArgs->output_matrix;
    struct CSRMatrix* merged = gridArgs->merged;
    int* grid = gridArgs->grid;   
     int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;
    bool* exists = (bool*)calloc(total + 1, sizeof(bool));
    if (exists == NULL) {
        printf("Memory allocation failed\n");
        return(0);
    }
    int x = 0;
    for(int i = 0; i <= (total/2)-1; i ++){
        if ( (!exists[grid[i]]) &&(grid[i] != grid[i + 1] )) {
                    *cur_row++ = num_matches;  // Initialize row pointer for the current row

            exists[grid[i]] = true; //
            ++num_matches;
            *cur_neighbour++ = grid[i];
            for (int j = merged->row_ptr[grid[i]]; j < merged->row_ptr[grid[i] + 1]; j++) {
                if (!exists[merged->col_indices[j]]) {
                    ++num_matches;
                    *cur_neighbour++ = merged->col_indices[j];
                    exists[merged->col_indices[j]] = true; //

                }
            }
        }
       
    }
    *cur_row = num_matches;
//  for (int i = 0; i < total/2; i++) {
//         if ( (grid[i] != grid[i + 1])
//          ) {
//         printf("Row %d: ",i);
//         for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
//             printf("%d ", csr->col_indices[j]);
//         }
//         printf("\n");
//      }
//     }


}


void* grid_p3(void * args){
    struct GridArgs* gridArgs = (struct GridArgs*) args;
    struct CSRMatrix* csr = gridArgs->output_matrix;
    struct CSRMatrix* merged = gridArgs->merged;
    int* grid = gridArgs->grid;   
     int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;
    bool* exists = (bool*)calloc(total + 1, sizeof(bool));
    if (exists == NULL) {
        printf("Memory allocation failed\n");
        return(0);
    }
    int x = 0;
    for(int i = 0; i <= (total/2)-1; i ++){
        if ( (!exists[grid[i]]) &&(grid[i] != grid[i + 1] )) {
                    *cur_row++ = num_matches;  // Initialize row pointer for the current row

            exists[grid[i]] = true; //
            ++num_matches;
            *cur_neighbour++ = grid[i];
            for (int j = merged->row_ptr[grid[i]]; j < merged->row_ptr[grid[i] + 1]; j++) {
                if (!exists[merged->col_indices[j]]) {
                    ++num_matches;
                    *cur_neighbour++ = merged->col_indices[j];
                    exists[merged->col_indices[j]] = true; //

                }
            }
        }
       
    }
    *cur_row = num_matches;
//  for (int i = 0; i < total/2; i++) {
//         if ( (grid[i] != grid[i + 1])
//          ) {
//         printf("Row %d: ",i);
//         for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
//             printf("%d ", csr->col_indices[j]);
//         }
//         printf("\n");
//      }
//     }
}


void* grid_p4(void * args){
    struct GridArgs* gridArgs = (struct GridArgs*) args;
    struct CSRMatrix* csr = gridArgs->output_matrix;
    struct CSRMatrix* merged = gridArgs->merged;
    int* grid = gridArgs->grid;   
     int num_matches = 0;
    int *cur_row = csr->row_ptr;
    int *cur_neighbour = csr->col_indices;
    bool* exists = (bool*)calloc(total + 1, sizeof(bool));
    if (exists == NULL) {
        printf("Memory allocation failed\n");
        return(0);
    }
    int x = 0;
    for(int i = 0; i <= (total/2)-1; i ++){
        if ( (!exists[grid[i]]) &&(grid[i] != grid[i + 1] )) {
                    *cur_row++ = num_matches;  // Initialize row pointer for the current row

            exists[grid[i]] = true; //
            ++num_matches;
            *cur_neighbour++ = grid[i];
            for (int j = merged->row_ptr[grid[i]]; j < merged->row_ptr[grid[i] + 1]; j++) {
                if (!exists[merged->col_indices[j]]) {
                    ++num_matches;
                    *cur_neighbour++ = merged->col_indices[j];
                    exists[merged->col_indices[j]] = true; //

                }
            }
        }
       
    }
    *cur_row = num_matches;
//  for (int i = 0; i < total/2; i++) {
//         if ( (grid[i] != grid[i + 1])
//          ) {
//         printf("Row %d: ",i);
//         for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
//             printf("%d ", csr->col_indices[j]);
//         }
//         printf("\n");
//      }
//     }
}


int main() {
    double elapsed; 
    clock_gettime(CLOCK_MONOTONIC, &start);    
    struct CSRMatrix csr1, csr2, csr3,csr4,csr_merged,csr5,csr6,csr7,csr8,csr9;
    pthread_t new_thread, new_thread2,new_thread3,new_thread4,new_thread5;
    pthread_t thread_g, thread_g2,thread_g3,thread_g4;
    int min = 1;
    int max = 100;
    srand(10);
    int* grid; int* grid2; int* grid3; int* grid4;
    grid = (int *)malloc(total/2 * sizeof(int));
    grid2 = (int *)malloc(total/2 * sizeof(int));
    grid3 = (int *)malloc(total/2 * sizeof(int));
    grid4 = (int *)malloc(total/2 * sizeof(int));

    int t = total/5;
    int t2 = 2*total/5;
    int t3 = total*3/5;
    int t4 = 4*total/5;
    int mid = (int)ceil((max-min)/2);
    int g1 = 0; int g2 = 0; int g3 = 0; int g4 = 0;
    for (int i = 0; i < total; i++) {
        int xcoor = generateRandomNumber(min, max);
        int ycoor = generateRandomNumber(min, max);
        array[i].xcoor = xcoor;
        array[i].ycoor = ycoor;
        if(xcoor < mid && ycoor >= mid){
            grid[g1] = i;
            g1 ++;            
        }
         if(xcoor >= mid && ycoor >= mid){
            grid2[g2] = i;
            g2 ++;            
        }
         if(xcoor < mid && ycoor < mid){
            grid3[g3] = i;
            g3 ++;            
        }
         if(xcoor >= mid && ycoor < mid){
            grid4[g4] = i;
            g4 ++;            
        }
    }
    
    construct_CSR( &csr1, total/5 );
    construct_CSR( &csr2, total/5 );
    construct_CSR( &csr3, total/5 );
    construct_CSR( &csr4, total/5 );
    construct_CSR( &csr5, total/5 );

    construct_CSR( &csr6, total/2 );
    construct_CSR( &csr7, total/2 );
    construct_CSR( &csr8, total/2 );
    construct_CSR( &csr9, total/2 );

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

struct GridArgs args1 = {&csr6, &csr_merged, grid};
struct GridArgs args2 = {&csr7, &csr_merged, grid2};
struct GridArgs args3 = {&csr8, &csr_merged, grid3};
struct GridArgs args4 = {&csr9, &csr_merged, grid4};


pthread_create(&thread_g, NULL, grid_p, &args1);
pthread_create(&thread_g2, NULL, grid_p2, &args2);
pthread_create(&thread_g3, NULL, grid_p3, &args3);
pthread_create(&thread_g4, NULL, grid_p4, &args4);

pthread_join(thread_g, NULL);
pthread_join(thread_g2, NULL);
pthread_join(thread_g3, NULL);
pthread_join(thread_g4, NULL);



clock_gettime(CLOCK_MONOTONIC, &finish);
elapsed = (finish.tv_sec - start.tv_sec);
elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution time: %.6f seconds\n", elapsed);
    // clean up

    // print_CSR2(&csr_merged);

    return 0;
}