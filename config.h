#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h> //usado na funcao chave
#include <time.h> //usado na funcao chave
#include <string.h>
#include <ctype.h>
#include <sodium.h>
#include <sqlite3.h>

#define HASH_SIZE crypto_pwhash_STRBYTES
#define TAMANHO_ALFABETO 26

//PROTOTIPOS
char *criptografia_substituicao (char *key, char *texto);
char* descriptografar_substituicao (char *key, char *texto_criptografado);
int menu(void);
char* get_string();
int home();

#endif