#include "config.h"

void shuffle(int *array){
    for(int i = TAMANHO_ALFABETO - 2; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}

char *chave_aleatoria(void){
    // criar um array de 0 a 25
    // embaralhar os numeros

}

int main(void){
    char *chave = chave_aleatoria();
    return 0;
}