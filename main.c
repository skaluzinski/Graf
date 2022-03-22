#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include"graph.h"
#include<windows.h>


int main (int argc, char**argv){
 
    //testowanie funkcji, generujacej wagi
    double min = atoi(argv[1]);
    double max = atoi(argv[2]);

    for(int i = 0; i < 10; i++){
        //sprawdzanie generowania liczb
        Sleep(1000);
        double weight = generateWeight(min, max);
        printf("Weight %d: %lf\n", i, weight);
    }
}