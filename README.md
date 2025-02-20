# **novcrypt**
Software de linha de comando com ferramentas para criptografar e descriptografar textos.

---
## 📖 **Manual**
Após fazer login, você poderá escolher entre duas opções: **Criptografar** ou **Descriptografar**.

![print]

**Criptografar**: Será gerada uma chave aleatória de 26 caracteres. Essa chave será necessária para descriptografar seu texto posteriormente.

**Descriptografar**: Você precisará informar a chave e o texto criptografado para que ele seja decifrado corretamente.

---
## 🧠 **Algoritmo**
O algoritmo utilizado é baseado na cifra de substituição, um método clássico de criptografia em que cada caractere do texto original é substituído por outro, de acordo com uma chave predefinida.

### Características da cifra de substituição:

- **Simplicidade**: Fácil de implementar e compreender.  
- **Chave fixa**: A mesma chave é usada tanto para criptografar quanto para descriptografar.
- **Reversibilidade**: O processo de descriptografia é simplesmente a inversão da substituição, desde que a chave correta seja conhecida.

  
Nesse caso, é gerada uma chave aleatória de 26 caracteres, garantindo uma substituição única para cada letra do alfabeto. Isso aumenta a segurança do processo, dificultando a quebra da criptografia sem a chave correta.
