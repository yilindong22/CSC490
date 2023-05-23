#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const int NPAD = 31;

typedef struct l {
  struct l *n;
  long int pad[NPAD];
}l;

int main() {
    

    int n = pow(2,19) / sizeof(struct l);


    l** rarr = malloc(n * sizeof(l*)); //random array

    struct l* head = NULL;
    head = malloc(sizeof(struct l));  //1
    l* node = head;  //head -> next 

    for (int i = 0; i < n-1; i++){  //creat more nodes and insert them into the array
        rarr[i] = node;
        node -> n = malloc(sizeof(struct l)); 
        node = node->n;
        node -> n = NULL;
    }
    struct l* curr = head;

    for(int i = 0; i < n; i++) { // shuffle the random array 
        int index1 = rand() % 10;
        int index2 = rand() % 10;
        l* temp = rarr[index1];
        rarr[index1] = rarr[index2];
        rarr[index2] = temp;
    }
    double time_spent = 0.0;

    clock_t begin = clock();
    while(head->n != NULL){
        head = head->n;
    }
    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The ran elapsed time is %f seconds", time_spent);

    return 0;
}
