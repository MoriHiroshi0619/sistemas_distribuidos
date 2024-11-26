# Trabalho prático 4 
Nesse diretorio estão os arquivos do trabalho 4 (prático) realizado pela dupla 

- **Mori Hiroshi** (rgm: 45380)
- **Rafael Florenciano** (rgm: 45385).

Mais especificamente, aqui tem os códigos na linguagem C feito para rodar em UNIX.

## Sinais
No caminho `./sinais/` temos os arquivos referentes ao primeiro exercício. <br> 
Mais especificamente nesse caminho temos 3 subdiretórios diferentes, cada um com um código ligeiramente diferente.

1. `busy_wait`: Nesse diretorio tem a implementação do código que utiliza um loop infinito para simular um processamento pesado.
<br> para compilar o código basta executar o comando
```bash
gcc receiver.c  -o receiver                                                                     
gcc sender.c -o sender 
```
Agora para executar o código basta rodar o comando `./receiver` que será exibido o pid do processo e o programa ficará esperando um sinal. <br>
Em outro terminal rodar o comando `./sender <PID> <SINAL>` para enviar o sinal.

2. `blocking_wait`: Nesse diretorio tem a implementação do código que utiliza a função `pause()` para esperar o sinal.
<br> para compilar o código basta executar o comando
```bash
gcc receiver.c  -o receiver                                                                     
gcc sender.c -o sender 
```
Agora para executar o código basta rodar o comando `./receiver` que será exibido o pid do processo e o programa ficará esperando um sinal. <br>
Em outro terminal rodar o comando `./sender <PID> <SINAL>` para enviar o sinal.

3. `ambos`: Nesse diretorio tem a implementaçãod de ambos acima, sendo passado como argumento qual dos dois códigos será executado.
<br> para compilar o código basta executar o comando
```bash
gcc receiver.c  -o receiver                                                                     
gcc sender.c -o sender 
```
Agora para executar o código basta rodar o comando `./receiver <blocking_wait/busy_wait>` aonde 1 é para blocking_wait e 2 é para busy_wait, será exibido o pid do processo e o programa ficará esperando um sinal. <br>
Em outro terminal rodar o comando `./sender <PID> <SINAL>` para enviar o sinal.

## Pipes
No caminho `./pipes_v1/`  e `./pipes_v2` temos os arquivos referentes ao segundo exercício. <br>

1. `v1`: Nesse diretorio tem a implementação do código que utiliza um pipe com o comando `mkfifo` para comunicação entre processos. <br>
Para testar esse código antes é necessario criar o pipe com o comando `mkfifo pipe` para criar o pipe. <br>
Agora para compilar o código basta executar o comando
```bash
gcc consumer.c -o consumer                                                                      
gcc producer.c -o producer
```
Feito isso, para executar o código basta rodar o comando `./consumer <pipe>` aonde pipe é o nome do pipe criado anteriormente. <br>
Em outro terminal rodar o comando `./producer <qtd_numeros> <pipe>` para enviar a mensagem, aonde qtd_numeros é a quantidade de números que serão enviados e pipe é o nome do pipe criado anteriormente.

2. `v2`: Nesse diretorio tem a implementação do código que utiliza um pipe com o comando `pipe` e `fork` para comunicação. <br>
Para compilar o código basta executar o comando
```bash
gcc produtor-consumidor.c -o produtor-consumidor
```
Para executar o código basta rodar o comando `./produtor-consumidor <qtd_numeros>` e será exibido o resultado.

## Socket
no caminho `./socket/` e `./sockets_it/` temos os arquivos referentes ao terceiro exercício. <br>

1. `socket`: Nesse diretorio tem a implementação do código que utiliza um socket para comunicação entre cliente e servidor. <br>
Para compilar o código basta executar o comando
```bash
gcc consumer.c -o consumer                                                                      
gcc producer.c -o producer
```
Feito isso, para executar o código basta rodar o comando `./consumer <porta>` aonde porta é a porta que será utilizada. (Recomendo a porta 8080)<br>
Em outro terminal rodar o comando `./producer <ip> <porta> <qtd_numeros>` para enviar a mensagem, aonde ip é o ip do servidor (127.0.0.1), porta é a porta que será utilizada (8080) e qtd_numeros é a quantidade de números que serão enviados.

2. `sockets_it`: Nesse diretorio tem a implementação do código que utiliza um socket para comunicação entre cliente e servidor, porém de maneira interativa <br>
para compilar o código basta executar o comando
```bash
gcc consumer.c -o consumer                                                                      
gcc producer.c -o producer
```
Aqui, para executar o código basta rodar o comando `./consumer <porta>` aonde porta é a porta que será utilizada. (Recomendo a porta 8080)<br>
Já no em outro terminal rodar o comando `./producer <ip> <porta>` para enviar a mensagem, aonde ip é o ip do servidor (127.0.0.1) e porta é a porta que será utilizada (8080).
Note que nesse código podemos passar a mensagem que será enviada pelo cliente.