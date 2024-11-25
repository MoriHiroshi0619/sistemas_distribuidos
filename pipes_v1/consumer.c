#include <stdio.h>  // printf, fscanf, perror, FILE, fopen, fclose
#include <stdbool.h> // bool, true, false

bool eh_primo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome do pipe>\n", argv[0]);
        return 1;
    }

    const char *pipe_name = argv[1];

    // Abre o pipe para leitura
    FILE *pipe = fopen(pipe_name, "r");
    if (!pipe) {
        perror("Erro ao abrir o pipe");
        return 1;
    }

    int number;
    while (fscanf(pipe, "%d", &number) != EOF) {
        if (number == 0) {
            printf("Consumidor: Recebido sinal de término. Encerrando...\n");
            break;
        }

        if (eh_primo(number)) {
            printf("Consumidor: %d é primo.\n", number);
        } else {
            printf("Consumidor: %d não é primo.\n", number);
        }
    }

    fclose(pipe); // Fecha o pipe
    return 0;
}
