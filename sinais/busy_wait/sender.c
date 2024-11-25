// gcc sender.c -o sender

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <PID> <Sinal>\n", argv[0]);
        printf("Sinais disponíveis:"
               "\n 1 - (SIGUSR1)"
               "\n 2 - (SIGUSR2)"
               "\n 3 - (SIGTERM) Encerra o programa\n");
        return 1;
    }

    int pid = atoi(argv[1]);
    int signal = atoi(argv[2]);

    // Verifica e mapeia o número do sinal para a macro correta
    switch (signal) {
        case 1: signal = SIGUSR1; break;
        case 2: signal = SIGUSR2; break;
        case 3: signal = SIGTERM; break;
        default:
            printf("Erro: Sinal inválido! Use 1 (SIGUSR1), 2 (SIGUSR2) ou 3 (SIGTERM).\n");
        return 1;
    }

    // Envia o sinal ao processo
    if (kill(pid, signal) == 0) {
        printf("Sinal %d enviado para o processo %d.\n", signal, pid);
    } else {
        perror("Erro ao enviar o sinal");
        return 1;
    }

    return 0;
}
