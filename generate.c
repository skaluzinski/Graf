#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include"graph.h"
#define COEF 0.001

double generateWeight(double min, double max){
    srand(time(NULL));
    double weight =((max - min)*((float)rand() / RAND_MAX)) + min; 

    return weight;
}

//graph_t generateGraph(int rows, int columns, double min, double max);
