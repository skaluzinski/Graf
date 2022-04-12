
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
    if(bfs(0,*graph)!=0){
        printf("Graf nie jest spójny.\n");
        return 1;
    }
    printf("Graf jest spójny.\n");
    return 0;
}
