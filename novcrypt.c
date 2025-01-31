#include "config.h"

char *chave(void)
{
    srand(time(NULL)); //usado para gerar um numero aleatorio com base no horario
    //variavel com todas letras do alfabeto
    const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    //cria uma nova variavel
    char *chave = malloc(27 * sizeof(char));
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        //cria um indice aleatorio
        int indice_aleatorio = rand() % TAMANHO_ALFABETO;
        //pega uma letra do alfabeto e adiciona na nova variavel atraves do indice aleatorio
        chave[i] = alfabeto[indice_aleatorio];
    }
    //cria um caractere nulo no fim da string
    chave[TAMANHO_ALFABETO + 1] = '\0';
    return chave;
}

char* get_string(void){
    
    size_t tamanho = 10, indice = 0;
    char *texto = malloc(tamanho * sizeof(char));
    //verificacao
    if(texto == NULL)
    {
        printf("alocação de memoria falhou \n");
        return NULL;
    }
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF);    
    while((caractere = getchar()) != '\n' && caractere != EOF)
    {
        if (indice + 1 >= tamanho)
        {
            tamanho *= 2;
            char *buffer_novo = realloc(texto, tamanho);
            //verificacao
            if(buffer_novo == NULL)
            {
                printf("alocação de memoria falhou \n");
                return NULL;
            }
            texto = buffer_novo;
        }
        texto[indice++] = caractere;
    }
    texto[indice] = '\0';

    return texto;
}

char* get_key(void){

    char key[TAMANHO_ALFABETO + 1];  // Buffer temporário para leitura
    scanf("%s", key);

    int tamanho_key = strlen(key);

    if (tamanho_key != TAMANHO_ALFABETO) {
        printf("A chave deve ter 26 dígitos\n");
        return NULL;
    }

    for (int i = 0; i < tamanho_key; i++) {
        if (!isalpha(key[i])) {
            printf("A chave deve ter apenas letras\n");
            return NULL;
        }
        // Checa letras repetidas
        for (int j = i + 1; j < tamanho_key; j++) {
            if (key[i] == key[j]) {
                printf("A chave não pode ter letras repetidas\n");
                return NULL;
            }
        }
    }

    // Aloca memória para armazenar a chave permanentemente
    char* result = malloc((tamanho_key + 1) * sizeof(char));
    if (result == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    strcpy(result, key);
    return result;
}

int main(int argc, char *argv[])
{
    // sair do programa, se login retorna 1
    menu();
    //if(menu() == 1) return 0;

    //verificacao uso correto - Isso sai - criar menu para decidir encrypt descrypt
    /*if(argc != 2)
    {
        printf("\nUse: \"novcrypt encrypt\" para criptografar ou \"novcrypt descrypt\" para descriptografar.\n\n");
        return 2;
    }*/
    
    /* //se criptografar ou descriptografar
    int caracteres_encrypt = 7;
    if(strlen(argv[1]) == caracteres_encrypt)
    {     
        char *key = chave();
        printf("Sua chave é %s\n", key);

        //pegar texto que vai ser criptografado
        printf("Digite o texto: ");
        char *texto = get_string();

        //printf("seu texto é: %s \n", texto);
        printf("seu texto criptografado é: %s\n", criptografia_substituicao (key, texto));

        free(texto);
        free(key);
        return 0;
    }else
    {
        //pedir chave
        printf("Qual sua chave: ");
        char *key = get_key();
        
        //pedir texto criptografado
        printf("Digite o texto: ");
        char *texto_descrypt = get_string();

        //funcao para descriptografar
        printf("seu texto descriptografado é: %s\n", descriptografar_substituicao(key, texto_descrypt));
        //retorna texto 
        free(texto_descrypt);
        return 0;
    }*/
}

