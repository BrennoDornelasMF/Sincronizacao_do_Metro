
#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t lock;

    pthread_cond_t car_available;
    pthread_cond_t boarding_changed;

    int waiting_passengers;
    int available_seats;
    int boarding_passengers;
    int boarding_open;
};

void station_init(struct station *station);

void station_load_car(struct station *station, int count);

void station_wait_for_car(struct station *station);

void station_on_board(struct station *station);

#endif