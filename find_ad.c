#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int total = 10;

struct Position {
    int xcoor;
    int ycoor;
    int adj[total + 1];
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
    srand(time(NULL)); // Set the seed for random number generation

    for (int i = 0; i < total; i++) {
        struct Position randomNums = {
            .xcoor = generateRandomNumber(min, max),
            .ycoor = generateRandomNumber(min, max),
            .adj = {0}  // Initialize adjacency array to zeros
        };
        array[i] = randomNums;
        printf("%d ", i);
    }

    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
            if (j != i && abs(array[i].xcoor - array[j].xcoor) <= epsilon &&
                abs(array[i].ycoor - array[j].ycoor) <= epsilon) {
                array[i].adj[j] = j;
            }
        }
    }

    // Print the adj array elements for each structure
    for (int i = 0; i < total; i++) {
         printf("\nx coor and Y coor for position %d is %d and %d: ", i,array[i].xcoor,array[i].ycoor);
        printf("\nadj elements for position %d: ", i);
        for (int j = 0; j <= total; j++) {
            printf("%d ", array[i].adj[j]);
        }
    }

    return 0;
}
