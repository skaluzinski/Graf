test1: test1.c generate.c
	$(CC) -o test1 test1.c generate.c
.PHONY: clean
	
clean:
	rm -f test1Graf test1
