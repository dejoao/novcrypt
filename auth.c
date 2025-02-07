#include "config.h"

char* new_senha(void){
    
    //iniciar biblioteca
    if (sodium_init() < 0) {
        printf("Erro ao inicializar a biblioteca libsodium.\n");
        return NULL;
    }

    //pedir senha do usuario
    char *senha = get_string(); 

    // Alocar memoria para guardar hash criada
    char *hash = malloc(HASH_SIZE);
    if (hash == NULL) {
        printf("Falha ao alocar memória para o hash.\n");
        free(senha);
        return NULL;
    }

    // Gera o hash da senha
    if (crypto_pwhash_str(hash, senha, strlen(senha),
            crypto_pwhash_OPSLIMIT_INTERACTIVE, // Limite de operações
            crypto_pwhash_MEMLIMIT_INTERACTIVE  // Limite de memória
        ) != 0) {
        printf("Falha ao gerar o hash.\n");
        free(senha);  
        free(hash);  
        return NULL;
    }

    free(senha); // Libera a memória da senha original
    return hash; // Retorna o hash gerado
}

int validador_login(sqlite3 *db, const char *email, const char *senha){
    sqlite3_stmt *stmt;
    const char *sql = "SELECT hash FROM autenticacao WHERE email = ?;";
   
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    //query
    int resultado = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Recuperar o hash armazenado no banco de dados
        const char *senha_db = (const char *)sqlite3_column_text(stmt, 0);

        // Comparar a senha digitada com o hash armazenado
        if (crypto_pwhash_str_verify(senha_db, senha, strlen(senha)) == 0) {
            resultado = 1;  // Senha correta
        }
    }

    sqlite3_finalize(stmt);
    return resultado;
}

int login(void){

    // Pegar email
    printf("Faça login\n\nEmail: ");
    char *email = get_string();
    //fazer verificacao email valido

    // Pegar senha usar hash
    printf("Senha: ");
    char *hash = new_senha();
    //printf("%s", hash);

    // Fazer consulta no banco de dados
    sqlite3 *db;
    if (sqlite3_open("auth.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (validador_login(db, email, hash)) {
        printf("Usuário autenticado com sucesso!\n");
    } else {
        printf("Falha na autenticação. Email ou senha incorretos.\n");
    }
    //Logado com sucesso mandar para tela inicial
    sqlite3_close(db);
    free(hash);
    return 0;
}

void cadastro(void){

    //Pegar email 
    printf("\nCrie sua conta\n\nEmail: ");
    char *email = get_string();
    //fazer verificacao email valido

    //guardar no banco de dados

    //Pegar senha //Fazer Hash
    printf("Senha: ");
    char *senha_hash = new_senha();
    
    //Guardar no banco de dados
    //Criado com sucesso
    //Mandar para o login

}

int menu(void){
    int opcao;

    printf("* ##   ##   #####   ##   ##    ####   ######   ###  ### ######    # ##### *\n");
    printf("* ###  ##  ### ###  ##   ##   ##  ##   ##  ##   ##  ##   ##  ##   ##  ##  *\n");
    printf("* #### ##  ##   ##  ##   ##  ##        ##  ##    ####    ##  ##     ## *\n");
    printf("* #######  ##   ##   ## ##   ##        #####      ##     #####      ## *\n");
    printf("* ## ####  ##   ##   ## ##   ##        ## ##      ##     ##         ## *\n");
    printf("* ##  ###  ### ###    ###     ##  ##   ## ##      ##     ##         ## *\n");
    printf("* ##   ##   #####     ###      ####   #### ##    ####   ####       #### *\n");
    printf("\n1. Login\n2. Cadastro\n3. Sair\n\n");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:
            //funcao login
            login();
            break;
        case 2:
            //funcao cadasstro
            cadastro();
            break;
        case 3:
            return 1;
            break;
        default:
            printf("Opção invalida.\n");
    }

    return 0;
}