
all: main

main: main.o
	gcc -g -m32 -Wall main.o -o main

main.o: main.c
	gcc -g -m32 -Wall -c main.c -o main.o

.PHONY:
	clean

clean:
	rm -f ./*.o main