#include "RWLock.h"

RWLock::RWLock() : reading(0), writing(0), writers(0) {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&turn, NULL);
}

void RWLock::rlock() {
    pthread_mutex_lock(&m);

    // Esperemos que todos los writers hayan terminado
    while(writers) {
        pthread_cond_wait(&turn, &m);
    }

    // Esperamos a que no haya mas gente escribiendo
    while(writing) {
        pthread_cond_wait(&turn, &m);
    }

    // Ya podemos leer
    reading++;
    pthread_mutex_unlock(&m);
}

void RWLock::wlock() {
    pthread_mutex_lock(&m);

    // Esperemos que todos los writers anteriores hayan terminado
    while(writers) {
        pthread_cond_wait(&turn, &m);
    }

    writers++;

    // Esperamos a que no haya mas gente tocando la estructura
    while(reading or writing) {
        pthread_cond_wait(&turn, &m);
    }

    // Ya podemos escribir
    writing++;
    pthread_mutex_unlock(&m);
}

void RWLock::runlock() {
    pthread_mutex_lock(&m);

    // Terminamos de leer
    reading--;

    // Avisarle a todos los writers que estén esperando
    pthread_cond_signal(&turn);
    pthread_mutex_unlock(&m);
}

void RWLock::wunlock() {
    pthread_mutex_lock(&m);

    // Terminamos de escribir
    writing--;
    writers--;

    // Avisarle a todos los readers y writers que estén esperando
    pthread_cond_broadcast(&turn);
    pthread_mutex_unlock(&m);
}
