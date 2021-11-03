all: main.o
	gcc -o fin main.o

main.o: main.c
	gcc -c main.c

run:
	./fin

clean:
	rm *.o
	rm fin
