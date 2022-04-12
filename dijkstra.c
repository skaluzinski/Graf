#include "graph.h"
#include "dijkstra.h"

// C code to implement Priority Queue
// using Linked List
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int isEmpty(pNode** pQueue)
{
  	if((*pQueue) == NULL){
    	return 1;
    }
  	return 0;
}

// Function to Create A New Node
pNode* newNode(int index, double cost)
{
    pNode* temp = malloc(sizeof(pNode));
    temp->index = index;
    temp->cost = cost;
    temp->next = NULL;
    return temp;
}
 
// Return the value at head
double getCost(pNode** pQueue)
{
    return (*pQueue)->cost;
}

int getIndex(pNode** pQueue)
{
    return (*pQueue)->index;
}
 
// Removes the element with the
// highest priority form the list
void pop(pNode** pQueue)
{
    pNode* temp = *pQueue;
    (*pQueue) = (*pQueue)->next;
    free(temp);
}
 
// Function to push according to priority
void addPNode(pNode** pQueue, int index, double cost)
{
    pNode* start = (*pQueue);
 
    // Create new Node
    pNode* temp = newNode(index, cost);
    if(isEmpty(pQueue)){
        (*pQueue) = temp;
        return;
    }
    if ((*pQueue)->cost > cost) {

        temp->next = *pQueue;
        (*pQueue) = temp;
    }
    else {
        while (start->next != NULL && start->next->cost < cost) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}
 
double* dijkstra(Graph graph,int start,int end){
    int *vis,*prev;
    double *dist;
    vis = malloc(graph.nOfVert * sizeof(int));
    prev = malloc(graph.nOfVert * sizeof(int));    
    dist = malloc(graph.nOfVert * sizeof(double));
    for(int i=0; i< graph.nOfVert;i++){
        vis[i] = -1;
        prev[i] = 0;
        dist[i] = INFINITY;
    }
    dist[start]=0;
    pNode* pq = newNode(start,0);
    while(!isEmpty(&pq)){
        int index = getIndex(&pq);
        double minValue = getCost(&pq);
        pop(&pq);
        vis[index] = 1;
        if (dist[index] < minValue){
            continue;
        }
        Node *edge = graph.array[index].head;
        while(edge != NULL){
            if(vis[edge->dest] == 1){
                edge = edge->next;
                continue;
            }
            double newDist = dist[index] + edge->weight;
            if (newDist < dist[edge->dest]){
                prev[edge->dest] = index;
                dist[edge->dest] = newDist;
                addPNode(&pq,edge->dest,newDist);
            }
            edge = edge->next;
            
        }
    }
    double *output = malloc(2* graph.nOfVert * sizeof(double));
    for(int i=0; i<graph.nOfVert;i++){
        output[i] = dist[i];
    }
    for(int i=0;i<graph.nOfVert;i++){
        output[i+graph.nOfVert] = prev[i];
    }
    return output;
}
int* findPath(Graph graph,int start,int end){
    int i;
    double *dist = malloc(graph.nOfVert * sizeof(double));
    double *joinedArrays =malloc(graph.nOfVert*2*sizeof(double));
    int* prev = malloc(graph.nOfVert * sizeof(int));
    joinedArrays = dijkstra(graph,start,end);
    for(i=0; i<graph.nOfVert;i++){
        
        dist[i] = joinedArrays[i];
    }
    for(i=0; i<graph.nOfVert;i++){
        prev[i] = joinedArrays[i+graph.nOfVert];
    }
    if(dist[end] == INFINITY){
        printf("Nie istnieje scieżka od %d do %d.\n",start,end);
        return NULL;
    }
    if(end > graph.nOfVert){
        printf("Węzeł %d nie znajduje się w tym grafie, ma on numery od 0 do %d",end,graph.nOfVert-1);
        return NULL;
    }
    int prevStep = end;
    i = graph.nOfVert-1;
    int* steps = malloc(graph.nOfVert * sizeof(int));
    while(prevStep != 0){
        steps[i--] = prevStep;
        prevStep = prev[prevStep];
    }
    printf("Waga drogi od %d do %d to %lf a sama droga to:\n\t %d",start,end,dist[end],start);
    for(i = 0; i<graph.nOfVert;i++){
        if(steps[i] == 0){
            continue;
        }
        printf(" -> %d ",steps[i]);
    }
    return steps;
}
