cmake_minimum_required(VERSION 3.29)
project(trabalho_pratico C)

set(CMAKE_C_STANDARD 11)

add_executable(trabalho_pratico sinais/blocking_wait/receiver.c
        sinais/blocking_wait/sender.c
        sinais/busy_wait/sender.c
        sinais/busy_wait/receiver.c
        sinais/ambos/receiver.c
        sinais/ambos/sender.c
        pipes_v1/producer.c
        pipes_v1/consumer.c
        sockets/consumer.c
        sockets/producer.c
)
