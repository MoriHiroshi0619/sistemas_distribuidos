// gcc receiver.c -o receiver

#include <signal.h> // sigaction, SIGUSR1, SIGUSR2, SIGTERM
#include <stdio.h>  // printf
#include <unistd.h> // getpid(), pause()
#include <stdlib.h> // exit()

// Handlers para diferentes sinais
void handle_signal1(int sig) {
    printf("Sinal SIGUSR1 recebido.\n");
}

void handle_signal2(int sig) {
    printf("Sinal SIGUSR2 recebido.\n");
}

void handle_exit(int sig) {
    printf("Sinal SIGTERM recebido. Encerrando o programa.\n");
    exit(0);
}

int main() {
    struct sigaction sa;

    // Configura handler para SIGUSR1
    sa.sa_handler = handle_signal1;
    sa.sa_flags = SA_RESTART; // Garante que chamadas bloqueantes sejam reiniciadas
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
    printf("Sinais disponíveis:"
           "\n 1 - (SIGUSR1)"
           "\n 2 - (SIGUSR2)"
           "\n 3 - (SIGTERM) Encerra o programa\n");

    // Loop para aguardar sinais
    while (1) {
        printf("DEBUG: Aguardando sinais...\n");
        pause(); // Bloqueia até receber um sinal
    }

    return 0;
}
