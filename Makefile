all: exec

run:
	./exec

exec: main.o personnage.o partie.o
	gcc *.o -o exec

main.o: main.c partie.h
	gcc -c main.c

personnage.o: personnage.c personnage.h
	gcc -c personnage.c

partie.o: partie.c partie.h personnage.h
	gcc -c partie.c

clean:
	rm -fr *.o