#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"
#include "graph.h"
int main(int argc,char** argv)
{
	Graph *graph = readGraph(argv[1]);
	int from,to;
	if (sscanf (argv[2], "%i", &from) != 1) {
    fprintf(stderr, "error - not an integer");
	}
	if (sscanf (argv[3], "%i", &to) != 1) {
    fprintf(stderr, "error - not an integer");
}
	findPath(*graph,from,to);
	//dijkstra(*graph,0,3);
	return 0;
		       }
