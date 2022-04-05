#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include"graph.h"

    int main(int argc, char **argv){
        srand(time(NULL));
        Graph *graph =genGraph(2, 19, 12, 13);
        printf("Zapisuję graf 12 x 13 o zmiennych z zakresu 2-19 w pliku: test1Graf \n");
        if (writeGraphToFile(graph,"test1Graf") == 0){
            printf("Zapisano pomyślnie\n");
            return 0;
        }
        printf("Nie udało się zapisać.\n");
        return -1;
}