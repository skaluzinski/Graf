#include "graph.h"
#ifndef BFS_H
#define BFS_H

struct queueNode {
	int item;
	struct queueNode* next;
};


struct Queue {
	struct queueNode *front, *back;
};

struct queueNode* newItem(int item);
int queuePop(struct Queue* queue);
struct Queue* createQueue();
void queueAdd(struct Queue* queue, int item);
int bfs(int source,Graph graph);
#endif
