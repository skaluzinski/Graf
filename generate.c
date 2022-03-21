#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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