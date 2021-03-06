#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#define NODE 2
#define VERTEX 1

double GenWeight(double min, double max)
{
    float random = ((double) rand()) / (double) RAND_MAX;
    double range = max - min;
    double waga = (random*range) + min;  
    return waga;
    
} 

Node* addNode(int dest, Graph* graph){
    Node* newNode = (struct Node*)malloc(sizeof(Node));
    newNode->dest =dest;
    newNode->weight = GenWeight(graph->min, graph->max);
    newNode->next = NULL;
    return newNode;
}
Node *addNodeParent(int dest, Graph *graph, double weightChild)
{
    Node *newNode = (struct Node *)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weightChild;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int parent, int dest){
    struct Node* temp = NULL;
    struct Node *newNode = addNode(dest, graph);


    if(graph->array[parent].head == NULL){              //If we sill do not have "neighbours" 
        newNode->next = graph->array[parent].head;      //we add pointer newNode -> next NULL
        graph->array[parent].head = newNode;            //And our head will point to newNode
    } else {
        temp = graph->array[parent].head;               
        while(temp->next != NULL){                      //If head already points to node
            temp = temp->next;                          //then we it-rate trough the list of our nodes till we find NULL
        }
        temp->next = newNode;                           //At the end of the list we add newNode
        temp->next->next = NULL;                        //and we add next pointer wich value is NULL
    }

    //also add an edge from dest to parent
    struct Node *newNodeParent = addNodeParent(parent, graph, newNode->weight);
    if (graph->array[dest].head == NULL)
    {
        newNodeParent->next = graph->array[dest].head;
        graph->array[dest].head = newNodeParent;
    }
    else
    {
        temp = graph->array[dest].head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNodeParent;
        temp->next->next = NULL;
}
}

void printGraph(Graph* graph){
    for(int i = 0; i < graph->nOfVert; i++){
        Node* nodes = graph->array[i].head;
        printf("\n Adjacency list of vertex %d\n head ", i);
        while(nodes){
            
			nodes = nodes->next;
			printf("-> %d [waga] %lf", nodes->dest, nodes->weight);
        }
    }
}

void genEdges(Graph *graph){
    int lastNode = (graph->rows -1);

    for(int i = 0; i <(graph->nOfVert)-(graph->rows); i++){
        
        if( i == lastNode){
            lastNode = graph->rows + i;
            addEdge(graph, i, i+(graph->rows));
        }else{
             addEdge(graph, i, i+1);
             addEdge(graph, i, i+(graph->rows));
        }
       
    }
    for(int i = graph->nOfVert-(graph->rows); i < graph->nOfVert-1; i++){
        addEdge(graph, i, i+1);
    }
}


Graph*  genGraph (double min, double max, int columns, int rows){
    int numOfVert = columns*rows;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->min = min;
    graph->max = max;
    graph->nOfVert = numOfVert;
    graph->columns = columns;
    graph->rows = rows;
    graph->array =(struct AdjList*)malloc(sizeof(AdjList)*numOfVert);

    //Initializing each adjacency list as empty
    for (int i = 0; i < numOfVert; i++){
        graph->array[i].head = NULL;
    }
    genEdges(graph);

    return graph;
}

Node* addNodeFromFile(int dest, Graph* graph, double weight){
    Node* newNode = (struct Node*)malloc(sizeof(Node));
    newNode->dest =dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
void addEdgeFromFile(Graph *graph, int parent, int dest, double weight){
    struct Node* temp;
    struct Node *newNode = addNodeFromFile(dest, graph,weight);
    temp = NULL;

    if(graph->array[parent].head == NULL){            
        newNode->next = graph->array[parent].head;      
        graph->array[parent].head = newNode;            
    } else {
        temp = graph->array[parent].head;               
        while(temp->next != NULL){                     
            temp = temp->next;                         
        }
        temp->next = newNode;                         
        temp->next->next = NULL;                       
    }
}

Graph *readGraph(char *nameOfFile){
    int nodeNum = 0, parent = 0,size;
    Graph* graph = malloc(sizeof(Graph));
    FILE *in = fopen(nameOfFile,"r");
    if(in == NULL){
	    printf("Couldn't open the file.\n");
        return NULL;
    }
    fseek(in, 0, SEEK_END); // seek to end of file
    size = ftell(in); // get current file pointer
    fseek(in, 0, SEEK_SET);
    if (fscanf(in,"%d %d", &graph->columns,&graph->rows)!= 2){
        printf("Couldn't read columns and rows.\n");
	    return NULL;
    }
    graph->nOfVert = graph->columns*graph->rows;
    graph->array =malloc(sizeof(AdjList)*graph->nOfVert);
    double weight;
    /*for (int i = 0; i < graph->nOfVert; i++){
        graph->array[i].head = NULL;
    }*/
    
    
    char *line =  malloc(size * sizeof(char));
    char* ptr;
    int part = NODE;
    while (fgets(line, 1024, in))
    {
        do {
            double num = strtod(line, &ptr);
            if(ptr == line) {
              if(strcmp(ptr,"\n")==0){
                parent++;
                break;
              }
              fprintf(stderr, "invalid format\n");
              break;
            }
            if(part == NODE){
                nodeNum = (int)num;
                part = VERTEX;
            }
            else{
                weight = num;
                part = NODE;
                //printf("%d->%d  %lf ",parent-1,nodeNum,weight);
                addEdgeFromFile(graph,parent-1,nodeNum,weight);
            }
            if(*ptr == ':' || *ptr == ' ') ptr++;
            line = ptr;
            } while(*ptr);
        }
        //printGraph(graph);
        return graph;
}

int writeGraphToFile(Graph* graph, char* name){
    FILE *fptr;
    int row, col, nodeNum;
    Node *tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph->columns,graph->rows);
    for(int i = 0; i < graph->nOfVert; i++){
        Node* nodes = graph->array[i].head;
        fprintf(fptr,"\t");
        while(nodes){
            fprintf(fptr," %d:%lf ", nodes->dest, nodes->weight);
            nodes = nodes->next;
        }
        if(i == graph->nOfVert -1)
            continue;
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return 0;
}


void freeGraph(Graph *graph){
        //Moze tutaj sprobowac inicjalizowac odrazu np temp, head = NULL;
    Node* temp,*head;
    temp, head = NULL;

    for(int i = 0; i < graph->nOfVert; i++){
        head = graph->array[i].head;
        temp = head;
        while(temp != NULL){
            free(temp);
            temp = temp->next;
        }

    }
    free(graph);

}
