#include <signal.h> // sigaction, SIGUSR1, SIGUSR2, SIGTERM
#include <stdio.h>  // printf
#include <unistd.h> // getpid()
#include <stdlib.h> // exit()

volatile sig_atomic_t signal_received = 0; // Variável compartilhada para busy wait

// Handlers para diferentes sinais
void handle_signal1(int sig) {
    printf("Sinal SIGUSR1 recebido.\n");
    signal_received = sig; // Atualiza o sinal recebido
}

void handle_signal2(int sig) {
    printf("Sinal SIGUSR2 recebido.\n");
    signal_received = sig; // Atualiza o sinal recebido
}

void handle_exit(int sig) {
    printf("Sinal SIGTERM recebido.\n");
    signal_received = sig; // Atualiza o sinal recebido
}

int main() {
    struct sigaction sa;

    // Configura handler para SIGUSR1
    sa.sa_handler = handle_signal1;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    // Configura handler para SIGUSR2
    sa.sa_handler = handle_signal2;
    sigaction(SIGUSR2, &sa, NULL);

    // Configura handler para SIGTERM
    sa.sa_handler = handle_exit;
    sigaction(SIGTERM, &sa, NULL);

    printf("Implementação busy wait\n");
    // Exibe informações iniciais
    printf("PID do processo: %d\n", getpid());
    printf("Sinais disponíveis:"
           "\n 1 - (SIGUSR1)"
           "\n 2 - (SIGUSR2)"
           "\n 3 - (SIGTERM) Encerra o programa\n");

    // Busy wait loop
    while (1) {
        if (signal_received) {
            // Verifica qual sinal foi recebido e reseta a variável
            if (signal_received == SIGTERM) {
                break; // Encerra o programa
            }
            signal_received = 0; // Reseta para aguardar o próximo sinal
        }
    }

    printf("Programa encerrado.\n");
    return 0;
}
