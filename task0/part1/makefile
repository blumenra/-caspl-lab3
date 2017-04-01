
all: bubblesort

bubblesort: bubblesort.o
	gcc -g -Wall bubblesort.o -o bubblesort

bubblesort.o: bubblesort.c
	gcc -g -Wall -c bubblesort.c -o bubblesort.o

.PHONY:
	clean

clean:
	rm -f ./*.o bubblesort