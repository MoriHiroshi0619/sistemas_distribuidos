# Trabalho prático 4 - Sistemas Distribuídos
Este repositório contém os arquivos do Trabalho Prático 4, desenvolvido pelos alunos:

- **Mori Hiroshi** (RGM: 45380)
- **Rafael Florenciano** (RGM: 45385)

Os códigos foram implementados em **linguagem C** e são compatíveis com sistemas **UNIX**.

# Estrutura do Repositório

## Sinais
Os códigos para o exercício de Sinais estão no diretório `./sinais/.` Esse diretório contém 3 subdiretórios com diferentes implementações:

### 1.1 - busy_wait
Implementação que utiliza um loop infinito para aguardar sinais, simulando processamento contínuo.

Compilação:
```bash 
gcc receiver.c -o receiver
gcc sender.c -o sender
```
Execução:
1. Inicie o **receiver**:
```bash
./receiver
```
O PID será exibido e o programa ficará aguardando sinais.

2. Em outro terminal, envie sinais com o **sender**:
```bash
./sender <PID> <SINAL>
```

### 1.2 - blocking_wait
Implementação que utiliza a função `pause()` para aguardar sinais de forma bloqueante.

Compilação:
```bash 
gcc receiver.c -o receiver
gcc sender.c -o sender
```
Execução:
1. Inicie o **receiver**:
```bash
./receiver
```
O PID será exibido e o programa ficará aguardando sinais.

2. Em outro terminal, envie sinais com o **sender**:
```bash
./sender <PID> <SINAL>
```

### 1.3 - Ambos
Implementação que combina as abordagens de blocking_wait e busy_wait, permitindo escolher o comportamento via parâmetro.

Compilação:
```bash
gcc receiver.c -o receiver
gcc sender.c -o sender
```
Execução:
1. Inicie o **receiver**:
```bash
./receiver <1 para blocking_wait | 2 para busy_wait>
```
O PID será exibido e o programa ficará aguardando sinais.

2. Em outro terminal, envie sinais com o **sender**:
```bash
./sender <PID> <SINAL>
```

## Pipes

Os códigos para o exercício de Pipes estão nos diretórios `./pipes_v1/` e `./pipes_v2/`.

### 2.1 - pipes_v1
Implementação que utiliza pipes nomeados criados com o comando `mkfifo`.

Configuração e Compilação:
1. Crie o pipe nomeado:
```bash
Configuração e Compilação:
```
2. Compile os códigos:
```bash
gcc consumer.c -o consumer
gcc producer.c -o producer
```
Execução:

1. Inicie o **consumer**:
```bash
./consumer <pipe>
```
Substitua `<pipe>` pelo nome do pipe criado.

2. Em outro terminal, inicie o **producer**:
```bash
./producer <qtd_numeros> <pipe>
```
Substitua `<qtd_numeros>` pela quantidade de números a gerar e `<pipe>` pelo nome do pipe.

### 2.2 - pipes_v2

Implementação que utiliza pipes anônimos criados com `pipe()` e comunicação entre processos com `fork()`.

Compilação:
```bash
gcc produtor-consumidor.c -o produtor-consumidor
```
Execução:
```bash
./produtor-consumidor <qtd_numeros>
```
Substitua `<qtd_numeros>` pela quantidade de números a gerar.

## Sockets

Os códigos para o exercício de Sockets estão nos diretórios `./socket/` e `./sockets_it/`.

### 3.1 - socket
Implementação básica de comunicação entre cliente e servidor utilizando sockets TCP.

Compilação:
```bash
gcc consumer.c -o consumer
gcc producer.c -o producer
```
Execução:
1. Inicie o **servidor**:
```bash
./consumer <porta>
```
Substitua `<porta> pelo número da porta (ex.: 8080).

2. Em outro terminal, inicie o **cliente**:
```bash
Substitua <porta> pelo número da porta (ex.: 8080)
```
Substitua `<ip>` pelo endereço IP do servidor (ex.: 127.0.0.1), `<porta>` pela porta utilizada, e `<qtd_numeros>` pela quantidade de números a enviar.

### 3.2 - sockets_it
Versão interativa da implementação de Sockets, permitindo que o cliente insira números manualmente.

Compilação:
```bash
gcc consumer.c -o consumer
gcc producer.c -o producer
```
Execução:
1. Inicie o **servidor**:
```bash
./consumer <porta>
```
Substitua `<porta>` pelo número da porta (ex.: 8080).

2. Em outro terminal, inicie o **cliente**:
```bash
./producer <ip> <porta>
```
Substitua `<ip>` pelo endereço IP do servidor (ex.: 127.0.0.1) e `<porta>` pela porta utilizada.

3. Digite os números no terminal do cliente. Para encerrar, envie 0.

## Notas Adicionais
- Todos os códigos desse Repository foram testados em um ambiente UNIX (Macintosh).
- Para compilar e executar os códigos, é necessário ter um compilador C instalado (ex.: GCC).
