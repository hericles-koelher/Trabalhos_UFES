all: Lab8

Lab8: *.o
	gcc -o Lab8 *.o -g -Wall -O2

*.o: *.c
	gcc -c *.c -g -Wall -O2

clean:
	rm -f *.o *.gch
