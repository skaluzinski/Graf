graf: graf.c generate.c bfs.c dijkstra.c graph.h 
		$(CC) -o graf graf.c generate.c graph.h dijkstra.c -ggdb

test1: test1.c generate.c
				$(CC) -o test1 test1.c generate.c
testBfs: bfs.c generate.c testBfs.c
				$(CC) -o testBfs testBfs.c generate.c bfs.c bfs.h graph.h 
testReading: testRead.c generate.c
				$(CC) -o testReading testRead.c graph.h
				$(./testReading)
				$(diff -s readGraph generatedGraph)
.PHONY: clean
				
clean:
				rm -f test1Graf test1 testBfs grafBfs generatedGraph readGraph testReading

