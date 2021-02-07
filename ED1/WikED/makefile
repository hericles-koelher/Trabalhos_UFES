all: wikied

wikied: listaGen.o tadContribuicao.o tadPag.o cliente.o
	gcc -o wikied cliente.o tadPag.o tadContribuicao.o listaGen.o

listaGen.o: listaGen.c
	gcc -c listaGen.c

tadContribuicao.o: tadContribuicao.c
	gcc -c tadContribuicao.c

tadPag.o: tadPag.c
	gcc -c tadPag.c

cliente.o: cliente.c
	gcc -c cliente.c
