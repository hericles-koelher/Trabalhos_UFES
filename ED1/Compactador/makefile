all: Trabalho instrucoes clean

Trabalho: Trabalho2.o arvore.o listaGen.o bitmap.o compactador.o descompactador.o
	gcc -o Trabalho Trabalho2.o arvore.o listaGen.o bitmap.o compactador.o descompactador.o -lm

Trabalho2.o: Trabalho2.c
	gcc -c Trabalho2.c

arvore.o: arvore.c
	gcc -c arvore.c

listaGen.o: listaGen.c
	gcc -c listaGen.c

bitmap.o: bitmap.c
	gcc -c bitmap.c

compactador.o: compactador.c
	gcc -c compactador.c

descompactador.o: descompactador.c
	gcc -c descompactador.c

rmproper: clean
	rm -rf betaTrab

instrucoes:
	gcc -o instrucoes instrucoes.c

clean:
	rm -rf *.o *.gch && ./instrucoes
