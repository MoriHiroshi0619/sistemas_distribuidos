#include <signal.h> // sigaction, SIGUSR1, SIGUSR2, SIGTERM
#include <stdio.h>  // printf
#include <unistd.h> // getpid(), pause()
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <1 para Blocking Wait | 2 para Busy Wait>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]); // Lê o modo (1 ou 2)

    if (mode != 1 && mode != 2) {
        printf("Modo inválido. Use 1 para Blocking Wait ou 2 para Busy Wait.\n");
        return 1;
    }

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

    // Exibe informações iniciais
    printf("PID do processo: %d\n", getpid());
    printf("Modo selecionado: %s\n", mode == 1 ? "Blocking Wait" : "Busy Wait");
    printf("Sinais disponíveis:"
           "\n 1 - (SIGUSR1)"
           "\n 2 - (SIGUSR2)"
           "\n 3 - (SIGTERM) Encerra o programa\n");

    if (mode == 1) {
        // Blocking Wait com pause()
        printf("Aguardando sinais (Blocking Wait)...\n");
        while (1) {
            pause(); // Bloqueia até receber um sinal
            if (signal_received == SIGTERM) break;
        }
    } else {
        // Busy Wait
        printf("Aguardando sinais (Busy Wait)...\n");
        while (1) {
            if (signal_received) {
                // Verifica qual sinal foi recebido
                if (signal_received == SIGTERM) break;
                signal_received = 0; // Reseta para aguardar o próximo sinal
            }
        }
    }

    printf("Programa encerrado.\n");
    return 0;
}
