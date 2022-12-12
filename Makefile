
all : prog

exec : ./prog
	./prog
prog : main.o exo1.o exo2.o
	gcc -o prog main.o exo1.o exo2.o


main.o: main.c
	gcc -o main.o -c main.c 

exo1.o: exo1.c
	gcc -o exo1.o -c exo1.c


exo2.o: exo2.c
	gcc -o exo2.o -c exo2.c


clean :                # Pour nettoyer le dossier d'origine. 
	rm -rf *.o

cleanall : clean 
	rm -rf prog

