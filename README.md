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
1. Autenticação
2. Interface
3. Banco de dados
