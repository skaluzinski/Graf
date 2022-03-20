#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct node{
    double left;
    double right;
    double up;
    double down
} node_t;

typedef struct graph{
    int rows;
    int cols;
    int min;
    int max;
    node_t* nodes;
} graph_t;

double randomNumber(double min,double max){
    double randNum =((float)(rand()%(int)max)+min)*((float)rand()/RAND_MAX);  
    return randNum;
}

int doEdgeExists(/*double probability*/){
    double random = ((double) rand()) / RAND_MAX;
    if(random > 0.5){
        return 1;
    }
    return -1;
}

void generateEdges(graph_t* graph) {
    graph->nodes = malloc(graph->cols * graph->rows *sizeof(node_t));
    int nodeNum;
    for(int row = 0; row < graph->rows; row++){
        for(int col = 0; col < graph->cols; col++){
            nodeNum =row*graph->cols+col ;
            (graph->nodes + nodeNum)->down = -1;
            (graph->nodes + nodeNum)->up = -1;
            (graph->nodes + nodeNum)->left = -1;
            (graph->nodes + nodeNum)->right = -1;
            if( row == 0 ) {//?generate lower edge
                (graph->nodes + nodeNum)->down = randomNumber(graph->min,graph->max);
            }
            else if( row == graph->rows ) { //?generate upper
                (graph->nodes + nodeNum)->up = randomNumber(graph->min,graph->max);
            }
            else { //?generate both
                (graph->nodes + nodeNum)->up = randomNumber(graph->min,graph->max);
                (graph->nodes + nodeNum)->down = randomNumber(graph->min,graph->max);
            }

            if( col == 0 ) {//?generate right edge
                (graph->nodes + nodeNum)->right = randomNumber(graph->min,graph->max);
            }
            else if( col == graph->cols) { //?generate left
                (graph->nodes + nodeNum)->left = randomNumber(graph->min,graph->max);
            }
            else {//generate both
                (graph->nodes + nodeNum)->right = randomNumber(graph->min,graph->max);
                (graph->nodes + nodeNum)->left = randomNumber(graph->min,graph->max);
            }
            printf("W%d \n\t%lf %lf %lf %lf \n",nodeNum,(graph->nodes + nodeNum)->right,(graph->nodes + nodeNum)->left,(graph->nodes + nodeNum)->up,(graph->nodes + nodeNum)->down);
        }
    }
}
int writeGraphToFile(graph_t graph, char* name){
    FILE *fptr;
    int row;
    char strleft[150];
    char strdown[150];
    char strup[150];
    char strright[150];
    char lineToWrite[600];
    int col,nodeNum;
    node_t tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph.cols,graph.rows);
    for(row = 0; row< graph.rows; row++){
        for(col = 0; col < graph.cols; col++){
            nodeNum =row*graph.cols+col ;
            fprintf(fptr,"   ");
            if((graph.nodes + nodeNum)->left != -1){
                fprintf(fptr,"  %d :%f",nodeNum-1, (graph.nodes + nodeNum)->left);
            }
            if((graph.nodes + nodeNum)->right != -1){
                fprintf(fptr,"  %d :%f",nodeNum+1, (graph.nodes + nodeNum)->right);
            }
            if((graph.nodes + nodeNum)->up != -1){
                fprintf(fptr,"  %d :%f",nodeNum-graph.cols, (graph.nodes + nodeNum)->up);
            }
            if((graph.nodes + nodeNum)->down != -1){
                fprintf(fptr,"  %d :%f",nodeNum+graph.cols, (graph.nodes + nodeNum)->down);
            }
            fprintf(fptr,"\n");
            
        }
    }
    fclose(fptr);
    return 0;
}