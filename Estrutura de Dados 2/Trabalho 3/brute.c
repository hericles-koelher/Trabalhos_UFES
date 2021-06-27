//
// Created by inccubus on 17/11/18.
//

#include "brute.h"
#include <stdlib.h>
#include <stdio.h>

void find_Password(Key password, Key T[N] , unsigned char buffer[C], int index){
    if(index < C){
        for(int i = 0; i < R; i++){
            buffer[index] = ALPHABET[i];
            find_Password(password,T,buffer,index+1);
        }
    }else{
        Key test_password = init_key(buffer);
        Key decrypted = subset_sum(test_password,T);
        if(!compare(decrypted,password)) print_key(test_password);
    }

}

int main(int argc, char** argv){
    if (argc != 2) {
        fprintf(stderr, "Usage: ./brute [encrypted password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    Key T[N];
    Key password = init_key((unsigned char *)argv[1]);

    //Leitura da tabela
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }

    find_Password(password,T,buffer,0);

    return 0;
}

