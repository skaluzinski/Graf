#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"graph.h"
#define MAXVALUE 9999999

typedef struct DijkstryItem
{
    double sumWeight; // Here could be list of nodes from where we can get weights and sum them
    int isChecked;
} DijkstryItem;

void printArr(DijkstryItem *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Number of Vertix : %d, Is checked : %d , Weight : %lf\n", i, array[i].isChecked, array[i].sumWeight);
    }
    printf("\n\n");
}

double AlgDijkstry(Graph *graph, int start, int finish)
{
    DijkstryItem *arr = malloc(sizeof(DijkstryItem) * graph->nOfVert);
    for (int i = 0; i < graph->nOfVert; i++)
    {
        arr[i].isChecked = 0;
        arr[i].sumWeight = INFINITY;
    }
    arr[start].isChecked = 1;
    arr[start].sumWeight = 0;

    Node *temp = graph->array[start].head;
    while (temp)
    {
        arr[temp->dest].sumWeight = temp->weight;
        temp = temp->next;
    }
    printArr(arr, graph->nOfVert);

    for (int j = 1; j < graph->nOfVert; j++)
    {

        int indexMin;
        double min = MAXVALUE;
        for (int i = 0; i < graph->nOfVert; i++)
        {
            if (arr[i].isChecked == 0 && arr[i].sumWeight < min)
            {
                min = arr[i].sumWeight;
                indexMin = i;
            }
        }

            temp = graph->array[indexMin].head;
            arr[indexMin].isChecked = 1;

            while (temp)
            {
                if (arr[temp->dest].sumWeight == MAXVALUE || arr[temp->dest].sumWeight > temp->weight + min)
                {
                    arr[temp->dest].sumWeight = temp->weight + min;
                }

                temp = temp->next;
            }
            printArr(arr, graph->nOfVert);
        }
        return 0;
    }

