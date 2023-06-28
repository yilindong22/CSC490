#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const int total = 20000;

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
    int B = 10;
    
   for (int t = 0;t < total; t+=B) {
     for (int j = t;j < total; j++) {
       for (int i = t;i < t+B; i++) {
            if (i != j){
                int xDiff = array[i].xcoor - array[j].xcoor;
                int yDiff = array[i].ycoor - array[j].ycoor;
             if((xDiff * xDiff + yDiff * yDiff) <= epsilon * epsilon) {
                array[i].adj[j] = j+1;
                array[j].adj[i] = i+1;
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
//         for (int j = 0; j < total; j++) {
//             printf("%d ", array[i].adj[j]);
//         }
//     }
    return 0;
}