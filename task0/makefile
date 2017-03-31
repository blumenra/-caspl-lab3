
all: bubblesort

bubblesort: bubblesort.o
	gcc -g -m32 -Wall bubblesort.o -o bubblesort

bubblesort.o: bubblesort.c
	gcc -g -m32 -Wall -c bubblesort.c -o bubblesort.o

.PHONY:
	clean

clean:
	rm -f ./*.o bubblesort