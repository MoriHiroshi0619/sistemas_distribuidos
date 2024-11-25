#include <stdio.h>   // printf, perror
#include <stdlib.h>  // atoi, exit
#include <stdbool.h> // bool, true, false
#include <string.h>  // memset
#include <unistd.h>  // close, read, write
#include <arpa/inet.h> // socket, bind, listen, accept, sockaddr_in

bool eh_primo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <porta>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Criação do socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configuração do endereço
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind do socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro no bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escuta de conexões
    if (listen(server_fd, 3) < 0) {
        perror("Erro ao escutar");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Consumidor aguardando conexões na porta %d...\n", port);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Erro ao aceitar conexão");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int number;
    while (read(new_socket, &number, sizeof(int)) > 0) {
        if (number == 0) {
            printf("Consumidor: Recebido sinal de término. Encerrando...\n");
            break;
        }

        // Verifica se o número é primo
        bool prime = eh_primo(number);
        printf("Consumidor: Número %d %s primo.\n", number, prime ? "é" : "não é");

        // Envia resposta ao Produtor
        write(new_socket, &prime, sizeof(bool));
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
