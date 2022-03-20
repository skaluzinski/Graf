
//moja wersja przechowywania grafu, żeby nie zapomnieć
#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    //Położenie węzłą w "macierze" w x k
    int w;
    int k;
    int numberOfVertex;
}Vertex;

typedef struct {
    Vertex vertex;
    Graph_t *next[4]; // wskaźnik na następną strukturę 
    // 0 - left, 1 - right , 2 - up, 3 - down
    double weight[4];

}Graph_t;


#endif