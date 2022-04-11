
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "generate.c"
int main(int argc, char** argv)
{
    char *command;
    command = "diff generatedGraph readGraph";
    int cols = argc > 1 ? atoi(argv[1]) : 10;
    int rows = argc > 2 ? atoi(argv[2]) : 10;
    double min = argc > 3 ? atof(argv[3]) : 1;
    double max = argc > 4 ? atof(argv[4]) : 5;
    Graph *graph = genGraph(min, max,cols,rows);
    Graph *graph2;
    writeGraphToFile(graph,"generatedGraph");
    graph2 = readGraph("generatedGraph");
    writeGraphToFile(graph2,"readGraph");
    int result = system(command);
    if(result ==0){
        printf("The files are the same, so both read and write functions work.\n");
        return 0;
    }
    else if(result == 1){
        printf("The files are different.");
        return 1;
    }
    else if(result == 2){
        printf("Diff returned 2, which means troubles in comparision.\n");
        return 2;
    }
    printf("System returned -1, failed to execute command.\n");
    return -1;
}
