FLAGS = -Wall -g

enc:
	gcc $(FLAGS) key.c encrypt.c -o encrypt

brute:
	gcc $(FLAGS) key.c brute.c -o brute -O3

decrypt:
	gcc $(FLAGS) decrypt.c key.c -o decrypt

clean:
	rm -f *.o a.out encrypt gmon.out prof brute decrypt