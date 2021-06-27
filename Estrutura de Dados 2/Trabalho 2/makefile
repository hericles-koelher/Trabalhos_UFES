all: EDII

EDII: *.o
	gcc -o EDII *.o -O2 -w

*.o: *.c
	gcc -c *.c -O2 -w

clean:
	rm -f *.o *.gch

run: EDII
	./EDII in/100.txt
