#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const int NPAD = 0;

typedef struct l {
  struct l *n;
  long int pad[NPAD];
}l;

int main() {
    int n = pow(2,28) / sizeof(struct l);


    l** rarr = malloc(n * sizeof(l*)); //random array
    l** sarr = malloc(n * sizeof(l*)); //sequential array

    struct l* head = NULL;
    head = malloc(sizeof(struct l));  //1
    l* node = head;  //head -> next 

    for (int i = 0; i < n-1; i++){  //creat more nodes and insert them into the array
        sarr[i] = node;
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

    return 0;
}
