#ifndef GRAPH_H
#define GRAPH_H

//A graph is an array od adjanc. list
//Size of an array is number of vertices in our graph 
typedef struct Graph{
    int nOfVert;
    double min; 
    double max;
    int columns;
    int rows;
    struct AdjList *array;
}Graph;

//Each element of array consists link (a "head") to a list of neighbours of def vertix 
typedef struct AdjList {
    struct Node *head;
}AdjList;

typedef struct Node{
    double weight;
    int dest;
    struct Node *next;
}Node;

double GenWeight(double min, double max);
Node* addNode(int dest, Graph* graph);
void addEdge(Graph *graph, int parent, int dest);
void printGraph(Graph* graph);
void genEdges(Graph *graph);
Graph* genGraph (double min, double max, int columns, int rows);
Node* addNodeFromFile(int dest, Graph* graph, double weight);
void addEdgeFromFile(Graph *graph, int parent, int dest, double weight);
Graph *readGraph(char *nameOfFile);
int writeGraphToFile(Graph* graph, char* name);
double AlgDijkstry(Graph *graph, int start, int finish);

#endif