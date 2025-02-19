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

char* get_string(void)
{
    char *entrada = NULL;
    size_t tamanho = 0;
    size_t caracteres_lidos;

    //limpa buffer
    if (stdin->_IO_read_ptr < stdin->_IO_read_end) { // Apenas no GNU C
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    caracteres_lidos = getline(&entrada, &tamanho, stdin);

    if (caracteres_lidos != -1) {
        // Removendo o '\n' do final, se presente
        if (entrada[caracteres_lidos - 1] == '\n') {
            entrada[caracteres_lidos - 1] = '\0';
        }
    } else {
        free(entrada);
        printf("Erro ao ler a entrada.\n");
    }

    return entrada;
}

char* get_key(void)
{

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

int home(void)
{
    int opcao;
    printf("\nESCOLHA OPÇÃO\n");
    printf("\n1. Criptografar\n2. Descriptografar\n\n");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:
            //funcao cripyt
            return 1;
            break;
        case 2:
            //funcao descrypt
            return 2;
            break;
        default:
            printf("Opção invalida.\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // se menu retornar 1 - login feito com sucesso: abre home; 
    // se retornar 2 sai do programa
    int opcaoMenu = menu();
    if(opcaoMenu == 1){
        //se home retornar 1: criptografar; se retornar 2: descriptografar
        int switchHome = home();
        if(switchHome == 1)
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
        }else if(switchHome == 2)
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
        }
    }else if(opcaoMenu == 2){
        return 0;
    }
}