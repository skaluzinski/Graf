
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "bfs.h"
#include "graph.h"
int main(int argc, char **argv){
    srand(time(NULL));
    Graph *graph =genGraph(2, 19, 20, 3);
    printf("Graf, którego spójność jest badana jest zapisany w pliku grafBfs.\n");
    writeGraphToFile(graph,"grafBfs");
    bfs(0,*graph);
    return 0;
}
