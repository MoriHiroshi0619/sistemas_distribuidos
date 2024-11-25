#include <stdio.h>   // printf, perror, scanf
#include <stdlib.h>  // exit
#include <stdbool.h> // bool
#include <unistd.h>  // close, read, write
#include <arpa/inet.h> // socket, connect, sockaddr_in

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <endereço IP> <porta>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

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

    printf("Produtor conectado ao servidor.\n");
    printf("Digite números inteiros para enviar (digite '0' para encerrar):\n");

    int number;
    while (1) {
        printf("Digite um número: ");
        scanf("%d", &number); // Lê número do usuário

        write(sock, &number, sizeof(int)); // Envia número ao Consumidor

        if (number == 0) {
            printf("Produtor: Enviado sinal de término.\n");
            break;
        }

        // Recebe resposta do Consumidor
        bool is_prime;
        read(sock, &is_prime, sizeof(bool));
        printf("Produtor: Número %d %s primo.\n", number, is_prime ? "é" : "não é");
    }

    close(sock); // Fecha o socket
    return 0;
}
