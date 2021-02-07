#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "str.h"
#include <string.h>

typedef struct {
    String *s;
    int index;
} Suffix;

Suffix* create_Suffix(String* str, int index){
    Suffix* new_Suffix = malloc(sizeof(Suffix));
    new_Suffix->index = index;
    new_Suffix->s = subString(str,index);

    return new_Suffix;
}

char Suffix_char_at(Suffix* c, int n){return char_at(c->s,n);}

String* input_From_File(char* name){
    FILE* file = fopen(name,"r");
    int n, new_Length = 0;
    char aux;
    fscanf(file, "%d\n", &n);

    char *temp = malloc(sizeof(char)*(n+1));

    while(fread(&aux,sizeof(char),1,file) == 1 && new_Length < n){
        if(isspace(aux) && isspace(temp[new_Length-1])) continue;
        if(isspace(aux) && aux != ' ') aux = ' ';

        temp[new_Length] = aux;
        new_Length++;
    }

    temp[new_Length] = '\0';

    String* out = create_string(temp);
    free(temp);
    fclose(file);

    return out;
}

Suffix* array_Suffix(String* str){
    Suffix* suf = malloc(sizeof(Suffix)*get_Length(str));

    for(int i = 0; i < get_Length(str); i++){
        suf[i] = *create_Suffix(str,i);
    }

    return suf;
}

int* search(Suffix* arr,int n, char* query){
  int* indexes = malloc(sizeof(int)*2);
  indexes[0] = indexes[1] = -1;

  int lo = 0, mid, hi = n-1;
  String *str;

  while (lo <= hi){
          mid = (lo + hi)/2;

          str = subString(arr[mid].s,arr[mid].index);

          if (!match(query, str)){
            destroy_string(str);
            break;
          }

          if (match(query, str) == -1)
               hi = mid-1;
          else
               lo = mid+1;

          destroy_string(str);
     }

     str = subString(arr[mid].s,arr[mid].index);

     if(!match(query, str)){
       int aux = mid;
       destroy_string(str);

       while(aux-1 >= 0){
         str = subString(arr[aux-1].s,arr[aux-1].index);
         if(!match(query, str)){
           aux--;
         }else{
           break;
         }
         destroy_string(str);
       }

       indexes[0] = aux;
       destroy_string(str);


       while(mid+1 < n){
         str = subString(arr[mid+1].s,arr[mid+1].index);
         if(!match(query, str)){
           mid++;
         }else{
           break;
         }
         destroy_string(str);
       }
       destroy_string(str);
       indexes[1] = mid;
     }

  return indexes;
}

static const int compare_Suffix(const void* x1, const void* x2){
    printf("MORREU\n");
  String* s1 = subString(((Suffix*)x1)->s,((Suffix*)x1)->index);
  String* s2 = subString(((Suffix*)x2)->s,((Suffix*)x2)->index);

  int result = compare(s1,s2);

  destroy_string(s1);
  destroy_string(s2);
    printf("TROLLEI\n");
  return result;
}

#define Tam 256

void reset_count_array(int* c, int R){
    for(int i = 0; i < R+2; i++) c[i] = 0;
}

void count_Sort(Suffix* vetor, Suffix* aux, int* count, int lo, int hi, int d, int R){

    reset_count_array(count,R);

    for(int i = 0; i <= hi; i++) count[Suffix_char_at(&vetor[i],d)+2]++;

    for(int i = 0; i < R+1; i++) count[i+1] = count[i];

    for(int i = lo; i <= hi; i++) aux[count[Suffix_char_at(&vetor[i],d)+1]++] = vetor[i];

    for(int i = lo; i <= hi; i++) vetor[i] = aux[i-lo];

}

int* create_count_array(int R){
    int* c = calloc(R+2, sizeof(int));
    return c;
}

void MSD_rec(Suffix* vetor, Suffix* aux, int lo, int hi, int d){
    if(hi <= lo) return;

    int* count = create_count_array(Tam);

    count_Sort(vetor,aux,count,lo,hi,d,Tam);

    for(int i = 1; i < Tam+1; i++){
        MSD_rec(vetor,aux,count[i]+lo,count[i+1]+lo-1,d+1);
    }


    free(count);
}

void sort(Suffix* vetor, int n){
    Suffix* aux = malloc(sizeof(Suffix)*n);
    MSD_rec(vetor,aux,0,n-1,0);
    free(aux);
}

int main(int argc, char** argv){

    String* str = input_From_File(argv[1]);
    //int context = atoi(argv[2]);

    Suffix* suf = array_Suffix(str);

    //qsort(suf,get_Length(str),sizeof(Suffix),compare_Suffix);
    sort(suf,get_Length(str));
    printf("ORDENOU\n\n");

    for(int i = 0; i < get_Length(str); i++){
        print_string(suf[i].s);
        printf("\n");
    }


    char *query = malloc(sizeof(char)*31);

    scanf("%s[^\n]",query);

    while(strcmp(query,"\n")){
      int *ind = search(suf,get_Length(str),query);

      if(ind[0] != -1){
        for(int i = ind[0]; i <= ind[1]; i++){
          String* auxStr = subString(suf[i].s,suf[i].index);
          print_string(auxStr);
          printf("\n");
          destroy_string(auxStr);
        }
      }

      scanf("%s[^\n]",query);
      printf("_____%s_____\n",query);
    }


}
