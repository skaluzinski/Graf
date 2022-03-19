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
    double randNum =((float)rand()/RAND_MAX)*(float)(max);

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
    int nodeNum;
    for(int row = 0; row < graph->rows; row++){
        for(int col = 0; col < graph->cols; col++){
            nodeNum =row*graph->cols+col ;
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
// format pliku:
//     col row
//         up down right left

int writeGraphToFile(graph_t graph, char* name){
    FILE *fptr;
    int row;
    char strleft[150];
    char strdown[150];
    char strup[150];
    char strright[150];
    char lineToWrite[600];
    int col;
    node_t tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph.cols,graph.rows);
    for(row = 0; row< graph.rows; row++){
        for(col = 0; col < graph.cols; col++){
            if((graph.nodes + col + row*graph.cols)->left != -1){
                sprintf(strleft, "%d :%lf",col+row*graph.cols-1, (graph.nodes + col + row*graph.cols)->left);
            }
            if((graph.nodes + col + row*graph.cols)->right != -1){
                sprintf(strright, "%d :%lf",col+row*graph.cols+1, (graph.nodes + col + row*graph.cols)->right);
            }
            if((graph.nodes + col + row*graph.cols)->up != -1){
                sprintf(strup, "%d :%lf",col+row*graph.cols-graph.cols, (graph.nodes + col + row*graph.cols)->up);
            }
            if((graph.nodes + col + row*graph.cols)->down != -1){
                sprintf(strdown, "%d :%lf",col+row*graph.cols+graph.cols, (graph.nodes + col + row*graph.cols)->down);
            }
            __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE
            fprintf(fptr,"\t\t%d :%lf");
        }
    }
}
int generateGraph(graph_t graph, char* name){
    if(graph.min > graph.max)
        {
            printf("Niepowodzenie generacji, minimalny zakres wartości wagi krawędzi jest większy od maksymalnego.\n");
            return -1;
        }
    graph.nodes = malloc(graph.cols * graph.cols *sizeof(node_t));
    generateEdges(graph);
}