#include "config.h"

char *criptografia_substituicao (char *key, char *texto)
{
    int n = strlen(texto);
    char *textoCriptografado = texto;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(texto[i]))
        {
            char base = isupper(texto[i]) ? 'A' : 'a';
            int indice = tolower(texto[i]) - 'a';
            
            // Verifica se o caractere é maiúsculo ou minúsculo e realiza a substituição
            textoCriptografado[i] = isupper(texto[i]) ? toupper(key[indice]) : tolower(key[indice]);
        }
        
    }
    return textoCriptografado;
}

char* descriptografar_substituicao (char *key, char *texto_criptografado)
{
   const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    int n = strlen(texto_criptografado);

    // Aloca memória para o texto descriptografado
    char *textoDescriptografado = malloc((n + 1) * sizeof(char));
    if (textoDescriptografado == NULL) {
        printf("alocação de memoria falhou \n");
        return NULL;
    }

    // Itera pelo texto cifrado
    for (int i = 0; i < n; i++) {
        if (isalpha(texto_criptografado[i])) {
            char base = isupper(texto_criptografado[i]) ? 'A' : 'a';
            char letraCifrada = tolower(texto_criptografado[i]);
            
            // Encontra a posição da letra cifrada na chave
            int indice = -1;
            for (int j = 0; j < TAMANHO_ALFABETO; j++) {
                if (key[j] == letraCifrada) {
                    indice = j;
                    break;
                }
            }

            // Substitui a letra com base no índice encontrado
            if (indice != -1) {
                textoDescriptografado[i] = base + indice;
            } else {
                textoDescriptografado[i] = texto_criptografado[i]; // Caso não encontre, mantém o caractere
            }
        } else {
            // Mantém caracteres que não são letras
            textoDescriptografado[i] = texto_criptografado[i];
        }
    }

    // Adiciona o terminador nulo
    textoDescriptografado[n] = '\0';

    return textoDescriptografado;
}