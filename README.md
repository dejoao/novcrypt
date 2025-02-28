# **novcrypt**
Software de linha de comando com ferramentas para criptografar e descriptografar textos.

---
## 📖 **Manual**
Após fazer login, você poderá escolher entre duas opções: **Criptografar** ou **Descriptografar**.

![Print do projeto](https://raw.githubusercontent.com/dejoao/novcrypt/main/src/print.png)

**Criptografar**: Será gerada uma chave aleatória de 26 caracteres. Essa chave será necessária para descriptografar seu texto posteriormente.

**Descriptografar**: Você precisará informar a chave e o texto criptografado para que ele seja decifrado corretamente.

---
## 🧠 **Algoritmos**
### Criptografia
O algoritmo utilizado é baseado na cifra de substituição, um método clássico de criptografia em que cada caractere do texto original é substituído por outro, de acordo com uma chave predefinida.

#### Características da cifra de substituição:

- **Simplicidade**: Fácil de implementar e compreender.  
- **Chave fixa**: A mesma chave é usada tanto para criptografar quanto para descriptografar.
- **Reversibilidade**: O processo de descriptografia é simplesmente a inversão da substituição, desde que a chave correta seja conhecida.

  
Nesse caso, é gerada uma chave aleatória de 26 caracteres, garantindo uma substituição única para cada letra do alfabeto. Isso aumenta a segurança do processo, dificultando a quebra da criptografia sem a chave correta.
***
### Hash da senha
O algoritmo utilizado é o Argon2id por meio da biblioteca libsodium. Ele transforma a senha em um hash seguro, dificultando a recuperação da senha original.

#### Características do Argon2id:
- **Segurança**: Protege contra ataques de força bruta e paralelos.
- **Parâmetros ajustáveis**: Permite configurar o consumo de memória e o tempo de processamento.
- **Resistência a ataques**: Projetado para ser resistente a ataques em hardware especializado (GPUs e ASICs).

A função `crypto_pwhash_str()` aplica esse algoritmo com limites de memória e operações pré-definidos para equilibrar segurança e desempenho.
***
## 🧰 **Funções** 
### 🔐 Sistema de Autenticação
O novcrypt utiliza um sistema simples e seguro para cadastro e validação de senhas, garantindo a integridade e a confidencialidade dos dados.

### Fluxo de Cadastro:
O usuário insere a senha.
A senha é processada e transformada em um hash seguro.
O hash gerado é armazenado para futuras verificações.

**Características do Cadastro**:

- O hash é gerado automaticamente e não armazena a senha original.
- Apenas o hash da senha é mantido, garantindo a privacidade do usuário.
- Erros durante o processo geram mensagens detalhadas.

### Fluxo de Login:
O usuário insere a senha.
O programa compara a senha fornecida com o hash armazenado.
Se a senha for válida, o acesso é concedido; caso contrário, uma mensagem de erro é exibida.

**Características do Login**:

- Comparação segura entre a senha fornecida e o hash armazenado.
- Validação robusta, protegida contra tentativas de adivinhação.
- Mensagens claras em caso de falha.
  
O sistema é projetado para ser simples de usar, com foco em segurança e clareza em cada etapa do processo.
***
### 🖥️ Interface
A interface do novcrypt é baseada em linha de comando (CLI), oferecendo uma experiência simples, direta e interativa para o usuário.

### Características da Interface:

**Menu Inicial**:

- Exibe opções para Login e cadastro.

**Clareza nas Mensagens**:

- Feedback para cada ação (sucesso ou erro).
- Instruções diretas para orientar o usuário em cada etapa.

**Facilidade de Navegação**:

- Entrada simplificada para selecionar opções.
- Mensagens amigáveis para confirmar operações.

A interface é projetada para ser prática e acessível, mantendo a simplicidade sem comprometer a usabilidade.
***
### 🗂️ Banco de Dados do novcrypt
O novcrypt utiliza um banco de dados SQL para armazenar e gerenciar as credenciais de forma organizada e segura. Garantindo a proteção de dados sensíveis.

### Estrutura do Banco de Dados:
A tabela principal armazena as informações essenciais para autenticação:

``` sql

CREATE TABLE autenticacao (
  id INTEGER PRIMARY KEY,
  email TEXT,
  hash TEXT
);
CREATE UNIQUE INDEX idx_email ON autenticacao (email);
```
**id**: Identificador único para cada usuário.  
**email**: Email cadastrado pelo o usuario (único).  
**hash**: Hash seguro gerado a partir da senha.
