
// C code to implement Priority Queue 
// using Linked List 
#include <stdio.h> 
#include <stdlib.h> 
#include "PriorityQueue.h"
  
  
// Function to Create A New Node 
PriorityQueue* create(int d, int p, int uid) 
{ 
    PriorityQueue* temp = (PriorityQueue*)malloc(sizeof(PriorityQueue)); 
    temp->data = d; 
    temp->priority = p; 
    temp->id = uid;
    temp->next = NULL; 
  
    return temp; 
} 
  
// Return the value at head 
int peek(PriorityQueue** head) 
{ 
    return (*head)->data; 
} 
  
// Removes the element with the 
// highest priority from the list 
void pop(PriorityQueue** head) 
{ 
    PriorityQueue* temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 
  
// Function to push according to priority 
void push(PriorityQueue** head, int d, int p, int uid)
{ 
    PriorityQueue* start = (*head); 
  
    // Create new Node 
    PriorityQueue* temp = create(d, p, uid);
  
    // Special Case: The head of list has lesser 
    // priority than new node. So insert new 
    // node before head node and change head node. 
    if ((*head)->priority > p) { 
  
        // Insert New Node before head 
        temp->next = *head; 
        (*head) = temp; 
    } 
    else { 
  
        // Traverse the list and find a 
        // position to insert new node 
        while (start->next != NULL && 
            start->next->priority <= p) { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        temp->next = start->next; 
        start->next = temp; 
    } 
} 
  
// Function to check is list is empty 
int isEmptyPQ(PriorityQueue** head) 
{ 
    return (*head) == NULL; 
} 
