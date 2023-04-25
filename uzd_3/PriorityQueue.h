#include <stddef.h>
#include <stdlib.h>
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct PriorityQueue { 
    int data; 
    // Lower values indicate higher priority 
    int priority;   
    int id;
    struct PriorityQueue* next; 
} PriorityQueue;

PriorityQueue* create(int d, int p, int uid);
int peek(PriorityQueue** head);
void pop(PriorityQueue** head);
void push(PriorityQueue** head, int d, int p, int uid);
int isEmptyPQ(PriorityQueue** head);

#endif