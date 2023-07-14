#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const int total = 20;

struct Position {
    int xcoor;
    int ycoor;
    int* adj; // Dynamic array
};

// Function to generate a random number within a given range
int generateRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int main() {
    int min = 1;
    int max = 100;
    int epsilon = 10;
    struct Position array[total];
    srand(10); // Set the seed for random number generation

    for (int i = 0; i < total; i++) {
        struct Position randomNums = {
            .xcoor = generateRandomNumber(min, max),
            .ycoor = generateRandomNumber(min, max),
            .adj = malloc(total * sizeof(int)) // Dynamically allocate the adj array
        };
        array[i] = randomNums;
    }

    clock_t start = clock();

    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
if (j != i && sqrt(pow(array[i].xcoor - array[j].xcoor, 2) + pow(array[i].ycoor - array[j].ycoor, 2))<= epsilon){                
                array[i].adj[j] = j+1;
             }
            }
            }
        
    

    clock_t end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", executionTime);

    for (int i = 0; i < total; i++) {
        printf("\nx coor and Y coor for position %d is %d and %d: ", i, array[i].xcoor, array[i].ycoor);
        printf("\nadj elements for position %d: ", i);
        for (int j = 0; j < total; j++) {
            if(array[i].adj[j] != 0){
            printf("%d ", array[i].adj[j]);
            }
        }
    }

    return 0;
}
