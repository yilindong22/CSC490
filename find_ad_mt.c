#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int total = 20000;
static const int tile_size = 2; // Choose a tile size that fits your data

struct Position {
    int xcoor;
    int ycoor;
    int* adj; // Dynamic array	
};

int generateRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int main() {
    int min = 1;
    int max = 100;
    int epsilon = 10;
    struct Position array[total];
    srand(10);

    for (int i = 0; i < total; i++) {
        struct Position randomNums = {
            .xcoor = generateRandomNumber(min, max),
            .ycoor = generateRandomNumber(min, max),
            .adj = malloc(total * sizeof(int)) // Dynamically allocate the adj array
        };
        array[i] = randomNums;
    }
   

    clock_t start = clock();

  for (int i = 0; i < total; i += tile_size) {
    for (int j = 0; j < total; j += tile_size) {
        for (int i2 = i; i2 < i + tile_size; i2++) {
            for (int j2 = j; j2 < j + tile_size; j2++) {
                if (j2 != i2 && abs(array[i2].xcoor - array[j2].xcoor) <= epsilon &&
                    abs(array[i2].ycoor - array[j2].ycoor) <= epsilon) {
                    array[i2].adj[j2] = j2;
                }
            }
        }
    }
}
    clock_t end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", executionTime);
//  for (int i = 0; i < total; i++) {
//          printf("\nx coor and Y coor for position %d is %d and %d: ", i,array[i].xcoor,array[i].ycoor);
//         printf("\nadj elements for position %d: ", i);
//         for (int j = 0; j <= total; j++) {
//             printf("%d ", array[i].adj[j]);
//         }
//     }
    return 0;
}