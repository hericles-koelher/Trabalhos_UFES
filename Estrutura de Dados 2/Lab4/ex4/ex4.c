#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 18

void sort(char a[M][N]) {
    // Implemente essa funcao para resolver a questao 4.
}

int main() {
    char a[M][N];

    // Le a entrada.
    for (int i = 0; i < M; i++) {
        fscanf(stdin,"%s", a[i]);
    }

    // Ordena.
    sort(a);

    // Exibe o resultado.
    for (int i = 0; i < M; i++) {
        printf("%s\n", a[i]);
    }
}
