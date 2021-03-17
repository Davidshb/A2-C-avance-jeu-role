all: exec

run:
	./exec

exec: main.o personnage.o
	gcc *.o -o exec

main.o: main.c personnage.h
	gcc -c main.c

personnage.o: personnage.c personnage.h
	gcc -c personnage.c