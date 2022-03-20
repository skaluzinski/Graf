#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define EMPTY -1
#define NODE 1
#define VERTEX 2
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
    if(graph->nodes == NULL){
        printf("Out of memory.");
        return;
    }
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
        }
    }
}


int writeGraphToFile(graph_t graph, char* name){
    FILE *fptr;
    int row, col, nodeNum;
    node_t *tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph.cols,graph.rows);
    for(row = 0; row< graph.rows; row++){
        for(col = 0; col < graph.cols; col++){
            nodeNum =row*graph.cols+col ;
            tempNode= graph.nodes + nodeNum;
            fprintf(fptr,"   ");
            if(tempNode->left != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-1, tempNode->left);
            }
            if(tempNode->right != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+1, tempNode->right);
            }
            if(tempNode->up != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-graph.cols, tempNode->up);
            }
            if(tempNode->down != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+graph.cols, tempNode->down);
            }
            fprintf(fptr,"\n");
            
        }
    }
    fclose(fptr);
    return 0;
}
graph_t readGraph(char *name){
    FILE *fptr;
    char line[1024];
    int rows,cols,nodeNum,difference;
    int lineNum = 0;
    char delim[] = " :\n";
    char *linePtr;
    node_t *tempNode;
    int currentPart = NODE;
    fptr = fopen(name,"r");
    if(fptr == NULL){
        printf("Failure while opening file named %s",name);
        // return NULL;
        //TODO
        //  Poprawić wartość zwracaną
    }
    fscanf(fptr,"%d %d ",&cols,&rows);
    graph_t graph;
    graph.nodes = malloc(cols * rows *sizeof(node_t));
    while(!feof(fptr)) {
        fgets(line, sizeof line, fptr);
        linePtr = strtok(line, delim);
        while(linePtr !=NULL)
        {
            if(currentPart == NODE){
                nodeNum = atoi(linePtr);
                currentPart = VERTEX;
            }
            else{
                difference = nodeNum-lineNum;
                *tempNode = graph.nodes[lineNum];
                tempNode->down = EMPTY;
                tempNode->up = EMPTY;
                tempNode->left = EMPTY;
                tempNode->right = EMPTY;
                if(difference == 1){
                    tempNode->right = atof(linePtr); 
                }
                else if(difference == -1){
                    tempNode->left = atof(linePtr); 
                }
                else if(difference == graph.cols){
                    tempNode->up = atof(linePtr); 
                }
                else{
                    tempNode->down = atof(linePtr); 
                }
                printf("  %d  :%lf",nodeNum,atof(linePtr));
                currentPart = NODE;
                
            }
		    linePtr = strtok(NULL, delim);
        }
        printf("\n");
        lineNum++;
    }
    fclose(fptr);
    return graph;
}