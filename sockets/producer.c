#include <stdio.h>   // printf, perror
#include <stdlib.h>  // atoi, exit
#include <stdbool.h> // bool
#include <string.h>  // memset
#include <unistd.h>  // close, read, write
#include <arpa/inet.h> // socket, connect, sockaddr_in
#include <time.h>    // time, srand, rand

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <endereço IP> <porta> <quantidade de números>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int num_to_generate = atoi(argv[3]);

    if (num_to_generate <= 0) {
        printf("Erro: forneça uma quantidade positiva de números.\n");
        return 1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;

    // Criação do socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Converte endereço IP
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Endereço inválido");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Conexão ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erro ao conectar");
        close(sock);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL)); // Inicializa gerador de números aleatórios
    int current_number = 1;

    for (int i = 0; i < num_to_generate; i++) {
        int delta = (rand() % 100) + 1;
        current_number += delta;

        printf("Produtor: Enviando número %d\n", current_number);
        write(sock, &current_number, sizeof(int)); // Envia número

        // Lê resposta do Consumidor
        bool is_prime;
        read(sock, &is_prime, sizeof(bool));
        printf("Produtor: Número %d %s primo.\n", current_number, is_prime ? "é" : "não é");
    }

    // Envia sinal de término
    int end_signal = 0;
    write(sock, &end_signal, sizeof(int));
    printf("Produtor: Enviado sinal de término.\n");

    close(sock);
    return 0;
}
