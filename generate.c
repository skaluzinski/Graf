#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define EMPTY -1
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
    int nodeNum,row,col;
    node_t *tempNode;
    double min = graph->min;
    double max = graph->max; 
    for(row = 0; row < graph->rows; row++){
        for(col = 0; col < graph->cols; col++){
            nodeNum =row*graph->cols+col ;
            tempNode= graph->nodes + nodeNum;
            tempNode->down = EMPTY;
            tempNode->up = EMPTY;
            tempNode->left = EMPTY;
            tempNode->right = EMPTY;
            if( row == 0 ) {//?generate lower edge
                tempNode->down = randomNumber(min,max);
            }
            else if( row == graph->rows -1) { //?generate upper
                tempNode->up = randomNumber(min,max);
            }
            else { //?generate both
                tempNode->up = randomNumber(min,max);
                tempNode->down = randomNumber(min,max);
            }

            if( col == 0 ) {//?generate right edge
                tempNode->right = randomNumber(min,max);
            }
            else if( col == graph->cols -1) { //?generate left
                tempNode->left = randomNumber(min,max);
            }
            else {//generate both
                tempNode->right = randomNumber(min,max);
                tempNode->left = randomNumber(min,max);
            }
            printf("W%d \n\t%lf %lf %lf %lf \n",nodeNum,tempNode->right,tempNode->left,tempNode->up,tempNode->down);
            printf("W%d \n\t%lf %lf %lf %lf \n",nodeNum,tempNode->right,tempNode->left,tempNode->up,tempNode->down);
        }
    }
}
int writeGraphToFile(graph_t graph, char* name){
    FILE *fptr;
    int row, col, nodeNum;
    node_t tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph.cols,graph.rows);
    for(row = 0; row< graph.rows; row++){
        for(col = 0; col < graph.cols; col++){
            nodeNum =row*graph.cols+col ;
            fprintf(fptr,"   ");
            if((graph.nodes + nodeNum)->left != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-1, (graph.nodes + nodeNum)->left);
            }
            if((graph.nodes + nodeNum)->right != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+1, (graph.nodes + nodeNum)->right);
            }
            if((graph.nodes + nodeNum)->up != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-graph.cols, (graph.nodes + nodeNum)->up);
            }
            if((graph.nodes + nodeNum)->down != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+graph.cols, (graph.nodes + nodeNum)->down);
            }
            fprintf(fptr,"\n");
            
        }
    }
    fclose(fptr);
    return 0;
}