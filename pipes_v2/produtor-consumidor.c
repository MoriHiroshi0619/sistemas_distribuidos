#include <stdio.h>   // printf, perror, snprintf
#include <stdlib.h>  // srand, rand, exit
#include <unistd.h>  // fork, pipe, read, write, close
#include <stdbool.h> // bool, true, false
#include <string.h>  // memset
#include <time.h>    // time

#define BUFFER_SIZE 20 // Tamanho fixo da string enviada pelo pipe

bool eh_primo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <quantidade de números a gerar>\n", argv[0]);
        return 1;
    }

    int num_to_generate = atoi(argv[1]); // Número de números a serem gerados
    if (num_to_generate <= 0) {
        printf("Erro: forneça uma quantidade positiva de números.\n");
        return 1;
    }

    int pipe_fd[2]; // Descritores do pipe: [0] leitura, [1] escrita

    // Cria o pipe
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar o pipe");
        return 1;
    }

    // Cria o processo filho
    pid_t pid = fork();
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        return 1;
    }

    if (pid == 0) {
        // Processo filho: Consumidor
        close(pipe_fd[1]); // Fecha a ponta de escrita do pipe

        char buffer[BUFFER_SIZE];
        while (1) {
            memset(buffer, 0, BUFFER_SIZE); // Limpa o buffer
            read(pipe_fd[0], buffer, BUFFER_SIZE); // Lê número do pipe
            int number = atoi(buffer); // Converte string para número

            if (number == 0) {
                printf("Consumidor: Recebido 0. Encerrando...\n");
                break;
            }

            // Verifica se o número é primo
            if (eh_primo(number)) {
                printf("Consumidor: %d é primo.\n", number);
            } else {
                printf("Consumidor: %d não é primo.\n", number);
            }
        }

        close(pipe_fd[0]); // Fecha a ponta de leitura
        exit(0);
    } else {
        // Processo pai: Produtor
        close(pipe_fd[0]); // Fecha a ponta de leitura do pipe

        srand(time(NULL)); // Inicializa gerador de números aleatórios
        int current_number = 1;

        char buffer[BUFFER_SIZE];
        for (int i = 0; i < num_to_generate; i++) {
            int delta = (rand() % 100) + 1;
            current_number += delta;

            snprintf(buffer, BUFFER_SIZE, "%d", current_number); // Converte número para string
            printf("Produtor: Gerando número %s\n", buffer);
            write(pipe_fd[1], buffer, BUFFER_SIZE); // Escreve no pipe
        }

        // Envia 0 para indicar fim
        snprintf(buffer, BUFFER_SIZE, "%d", 0);
        write(pipe_fd[1], buffer, BUFFER_SIZE);
        printf("Produtor: Enviado 0. Encerrando...\n");

        close(pipe_fd[1]); // Fecha a ponta de escrita
        wait(NULL);        // Espera o processo filho terminar
    }

    return 0;
}
