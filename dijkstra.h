#ifndef DIJKSTRA_H
#define DIJKSTRA_H
typedef struct pNode {
	int index;
 	double cost;
	struct pNode* next;
} pNode;

pNode* newNode(int index, double cost);
double getCost(pNode** pQueue);
int getIndex(pNode** pQueue);
void pop(pNode** pQueue);
void addPNode(pNode** pQueue, int index, double cost);
int isEmpty(pNode** pQueue);
double* dijkstra(Graph graph, int start, int end);
int* findPath(Graph graph,int start,int end);
#endif