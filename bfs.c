
#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "graph.h"

struct queueNode* newItem(int item)
{
	struct queueNode* temp = malloc(sizeof(struct queueNode));
	temp->item = item;
	temp->next = NULL;
	return temp;
}

int queuePop(struct Queue* queue)
{
	if (queue->front == NULL){
		return -1;
	}
	int lastElement = queue->back->item; 
	struct queueNode* temp = queue->front;
	queue->front = queue->front->next;

	if (queue->front == NULL){
	    queue->back = NULL;
	}
	free(temp);
    return lastElement;
    
}

struct Queue* createQueue()
{
	struct Queue* queue = malloc(sizeof(struct Queue));
	queue->front = queue->back = NULL;
	return queue;
}

void queueAdd(struct Queue* queue, int item)
{
	struct queueNode* temp = newItem(item);
	if (queue->back == NULL) {
		queue->front = temp;
		queue->back = temp;
		return;
	}
	queue->back->next = temp;
	queue->back = temp;
}


int bfs(int source, Graph graph){
    struct Queue* queue;
    int node;printf("11111\n");

    queue = malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->back = NULL;
    struct Node* temp;
    int i;
    int next;
    int nOfNeightbours;
    int *neighbours;
    neighbours = malloc(graph.nOfVert * graph.nOfVert);
    queueAdd(queue,source);
    int* visited; 
    visited = malloc(graph.nOfVert *  sizeof(int));
    int* previous = malloc(graph.nOfVert *  sizeof(int));
    for(int i=0;i<graph.nOfVert;i++){
        visited[i]=0;
        previous[i]=0;
    }
    visited[source] = 1;
    while(queue->front != NULL){
        node = queuePop(queue);
        nOfNeightbours = 0;
        temp = graph.array[node].head;
        while(temp != NULL){
            neighbours[nOfNeightbours] = temp->dest;
            nOfNeightbours++;
            temp = temp->next;
        }
        for( i = 0; i < nOfNeightbours; i++){
            next = neighbours[i] ;
            if( visited[next] != 1){
                queueAdd(queue,next);
                visited[next] = 1;
                previous[next] = node;
            }
        }
    }
    for(i = 0; i<graph.nOfVert; i++){
        if(visited[i] != 1){
            return -1;
            }
    }
    return 0;
}
