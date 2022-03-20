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
    node_t *tempNode;
    double min = graph->min;
    double max = graph->max; 
    for(int row = 0; row < graph->rows; row++){
        for(int col = 0; col < graph->cols; col++){
            nodeNum =row*graph->cols+col ;
            tempNode= graph->nodes + nodeNum;
            tempNode->down = -1;
            tempNode->up = -1;
            tempNode->left = -1;
            tempNode->right = -1;
            if( row == 0 ) {//?generate lower edge
                tempNode->down = randomNumber(min,max);
            }
            else if( row == graph->rows ) { //?generate upper
                tempNode->up = randomNumber(min,max);
            }
            else { //?generate both
                tempNode->up = randomNumber(min,max);
                tempNode->down = randomNumber(min,max);
            }

            if( col == 0 ) {//?generate right edge
                tempNode->right = randomNumber(min,max);
            }
            else if( col == graph->cols) { //?generate left
                tempNode->left = randomNumber(min,max);
            }
            else {//generate both
                tempNode->right = randomNumber(min,max);
                tempNode->left = randomNumber(min,max);
            }
            printf("W%d \n\t%lf %lf %lf %lf \n",nodeNum,tempNode->right,tempNode->left,tempNode->up,tempNode->down);
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