#include <stdio.h>  // printf, fprintf, perror, FILE, fopen, fclose, fflush
#include <stdlib.h> // atoi, srand, rand
#include <unistd.h> // unlink (caso necessário remover pipe no final)
#include <time.h>   // time (para inicializar srand)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <quantidade de números> <nome do pipe>\n", argv[0]);
        return 1;
    }

    int num_to_generate = atoi(argv[1]);
    if (num_to_generate <= 0) {
        printf("Erro: forneça uma quantidade positiva de números.\n");
        return 1;
    }

    const char *pipe_name = argv[2];

    // Abre o pipe para escrita
    FILE *pipe = fopen(pipe_name, "w");
    if (!pipe) {
        perror("Erro ao abrir o pipe");
        return 1;
    }

    srand(time(NULL)); // Inicializa gerador de números aleatórios
    int current_number = 1;

    for (int i = 0; i < num_to_generate; i++) {
        int delta = (rand() % 100) + 1;
        current_number += delta;

        printf("Produtor: Gerando número %d\n", current_number);
        fprintf(pipe, "%d\n", current_number); // Escreve no pipe
        fflush(pipe); // Garante que os dados sejam enviados imediatamente
    }

    printf("Produtor: Enviando sinal de término (0).\n");
    fprintf(pipe, "0\n"); // Envia sinal de término
    fflush(pipe);

    fclose(pipe); // Fecha o pipe
    return 0;
}
