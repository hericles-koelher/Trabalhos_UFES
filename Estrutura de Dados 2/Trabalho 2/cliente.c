#include "bin_packing_solution.h"

static int compare(const void* x1, const void* x2){
    return *((int*)x2) - *((int*)x1);
}

int main(int argc, char **argv){
    FILE *input = fopen(argv[1],"r");

    if(!input){
      printf("Erro na leitura do arquivo.\nEncerrando execução.\n");
      return 0;
    }

    int n;
    if(fscanf(input, "%d",&n) != 1){
      printf("Arquivo corrompido ou com formatação diferente do esperado\nEncerrando execução.");
      return 0;
    }

    int *numbers = malloc(sizeof(int)*n);

    for(int i = 0; i < n; i++){
        fscanf(input,"%d\n",&numbers[i]);
    }

    fclose(input);

    printf("Worst-Fit: %d\n", worst_fit(numbers,n));

    printf("Best-Fit: %d\n", best_fit(numbers,n));

    qsort(numbers,n,sizeof(int),compare);

    printf("Worst-Fit Decrescente: %d\n",worst_fit(numbers,n));

    printf("Best-Fit Decrescente: %d\n",best_fit(numbers,n));

    free(numbers);

    return 0;
}
