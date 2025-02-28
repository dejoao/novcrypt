#include "config.h"






char *chave_aleatoria(void){
    // criar um array de 0 a 25
    int *numeros = malloc((TAMANHO_ALFABETO) * sizeof(int));
    if (!numeros) return NULL;

    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        numeros[i] = i;
    }

    // embaralhar os numeros
    shuffle(numeros);
    
    const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";

    // cria a chave
    char *chave = malloc((TAMANHO_ALFABETO + MIN) * sizeof(char));
    if(!chave){
        free(numeros);
        return NULL;
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        chave[i] = alfabeto[numeros[i]];
    }

    //cria um caractere nulo no fim da string
    chave[TAMANHO_ALFABETO] = '\0';
    
    free(numeros);
    return chave;
}

int main(void){
    

    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        char *chave = chave_aleatoria();
        printf("\t%s\n", chave);
        free(chave);
    }
    
    return 0;
}