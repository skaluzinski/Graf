#ifndef GRAPH_H
#define GRAPH_H


typedef struct edge{
    node_t *destination;
    double weight;
} edge_t;

typedef struct node{
    //int nOfNode;
    int edgesAmount;
    edge_t *edges;
} node_t;

typedef struct graph{
    int rows;
    int cols;
    int min;
    int max;
    node_t* nodes;
} graph_t;

graph_t readGraph(char* nameOfFile);
graph_t generateGraph(int rows, int columns, double min, double max);
int checkIntegrity(graph_t graph);
double* findPath(graph_t graph);

#endif