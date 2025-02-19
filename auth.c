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
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Recuperar o hash armazenado no banco de dados
        const char *senha_db = (const char *)sqlite3_column_text(stmt, 0);

        // Comparar a senha digitada com o hash armazenado Funcao crypto_pwhash_str_verify()
        if (crypto_pwhash_str_verify(senha_db, senha, strlen(senha)) == 0) {
            sqlite3_finalize(stmt);
            return 0;  // Senha correta
        }
    }

    sqlite3_finalize(stmt);
    return 1;
}

int login(void){

    // Pegar email
    printf("Faça login\n\nEmail: ");
    char *email = get_string();
    //fazer verificacao email valido

    // Pegar senha usar hash // Nao esta dando certo porque nao posso criar um novo hash, 
    // a libsodium tem uma funcao para comparar as senhas
    printf("Senha: ");
    char *senha = get_string();
    //printf("%s", hash);

    // Fazer consulta no banco de dados
    sqlite3 *db;
    if (sqlite3_open("auth.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (validador_login(db, email, senha) == 0) {
        printf("Usuário autenticado com sucesso!\n"); //Logado com sucesso mandar para tela inicial
        sqlite3_close(db);
        free(senha);
        return 0;
    } else {
        printf("Falha na autenticação. Email ou senha incorretos.\n");
        sqlite3_close(db);
        free(senha);
        return 1;
    }
}

int insert_sql(sqlite3 *db, const char *email, const char *senha){
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO autenticacao (email, hash) VALUES (?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    // verifica se a consulta foi preparada com sucesso
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // insere dinamicamente os dados na consulta (?, ?)
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, senha, -1, SQLITE_TRANSIENT);

    // executa a consulta
    int step = sqlite3_step(stmt);
    // verifica se a consulta foi executada com sucesso
    if(step == SQLITE_CONSTRAINT){
        sqlite3_finalize(stmt); 
        return 2; // se o email ja existe
    }
    if (step != SQLITE_DONE) {
        fprintf(stderr, "Erro ao inserir no banco: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;

}

int cadastro(void){
    // Solicita o email 
    printf("\nCrie sua conta\n\nEmail: ");
    char *email = get_string();

    // Solicita a senha e faz o hash
    printf("Senha: ");
    char *senhaHash = new_senha();
    
    // Ponteiro para o banco de dados
    sqlite3 *db;

    // Abre o banco de dados e verifica erros
    if(sqlite3_open("auth.db", &db) != SQLITE_OK){
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    // Insere os dados no banco de dados e verifica erros
    int retornoIsert = insert_sql(db, email, senhaHash);
    if(retornoIsert == 1){
        printf("Erro ao criar cadastro!\n");
        free(senhaHash);
        sqlite3_close(db);
        return 1;        
    }else if(retornoIsert == 2){
        printf("Esse email ja existe: Insira outro\n"); // se retorna 2 email existente
        free(senhaHash);
        sqlite3_close(db);
        return 1; 
    } 

    printf("Cadastro criado com sucesso!\n");
    free(senhaHash);
    sqlite3_close(db);
    return 0;
    
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
            return 1; // login com sucesso
            break;
        case 2:
            //funcao cadastro
            cadastro();
            break;
        case 3:
            return 2;
            break;
        default:
            printf("Opção invalida.\n");
    }

    return 0;
}