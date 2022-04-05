#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "graph.h"

    int main(int argc, char **argv){
        // srand(time(NULL));
        // if(argc < 3){
        //     fprintf(stderr,"Proszę podać jako pierwszy argument ilość kolumn, a drugi ilość wierszy do wygenerowania");
        //     return 1;
        // }
        // int columns = atoi(argv[1]);
        // int rows = atoi(argv[2]);
        // Graph *graph =genGraph(2, 19, columns, rows);
        Graph *graph = readGraph("test.txt");
        printf("number of vert: %d ", graph->nOfVert);
        printGraph(graph);
        return 0;
}