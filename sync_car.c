#include "sync_car.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void check_pthread(int error, const char *operation)
{
    if (error != 0) {
        fprintf(stderr, "Erro ao %s: %s\n",
                operation, strerror(error));
        exit(EXIT_FAILURE);
    }
}

void station_init(struct station *station)
{
    station->waiting_passengers = 0;
    station->available_seats = 0;
    station->boarding_passengers = 0;
    station->boarding_open = 0;

    check_pthread(
        pthread_mutex_init(&station->lock, NULL),
        "inicializar o mutex da estação"
    );

    check_pthread(
        pthread_cond_init(&station->car_available, NULL),
        "inicializar a condição de disponibilidade de vagas"
    );

    check_pthread(
        pthread_cond_init(&station->boarding_changed, NULL),
        "inicializar a condição de atualização do embarque"
    );
}


void station_wait_for_car(struct station *station)
{
    check_pthread(
        pthread_mutex_lock(&station->lock),
        "adquirir o mutex da estação"
    );

    station->waiting_passengers++;

    while (!station->boarding_open ||
           station->available_seats== 0) {
        check_pthread(
            pthread_cond_wait(
                &station->car_available,
                &station->lock
            ),
            "aguardar uma vaga no carro"
        );
    }

    station->available_seats--;
    station->waiting_passengers--;
    station->boarding_passengers++;

    check_pthread(
        pthread_mutex_unlock(&station->lock),
        "liberar o mutex da estação"
    );
}