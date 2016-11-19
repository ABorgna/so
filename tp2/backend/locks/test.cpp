#include "RWLock.h"

#include <cassert>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h>

using namespace std;

#define CANT_THREADS 60

#define test(fn)                           \
    do {                                   \
        cout << "running " << #fn << endl; \
        fn();                              \
    } while (0)

class RWLockTester : public RWLock {
    // Non thread safe
   public:
    bool isWriting() { return writing; }
    bool isReading() { return reading; }
    bool isLocked() { return writing or reading; }
    int writersLeft() { return writers; }
    int readersLeft() { return reading; }
};

int variable_global = 0;
RWLockTester lock;
sem_t contador, escribir, leer;

void *lecturas_concurrentes(void*) {

    lock.rlock();
    std::cout << "Nuevo lector, cantidad total:" << lock.readersLeft() << std::endl;

    if (lock.readersLeft() < CANT_THREADS) {
        sem_wait(&contador);
    } else {
        assert(lock.readersLeft() == CANT_THREADS);
        for (int i = 0; i< CANT_THREADS; ++i)
            sem_post(&contador);
    }
    lock.runlock();
    return nullptr;
}

// Test inanición 1 --------------------------------------------------------
// lector llega, libera escritor para que se declare writer y
// antes de terminar también larga la tanda de lectores (que deben esperar)
// de lo contrario podrían generarle inanición al escritor
void *lector_t1(void*) {
    lock.rlock();
    sem_post(&escribir);
    // Escritor todavía no puede tomar el lock (no lo solté)
    // pero sí declararse como writer
    // lo esperamos. No podemos usar vc o semáforo porque
    // la declaración de writer sucede durante el wlock.
    while (lock.writersLeft() == 0)
        usleep(100000);

    for (int i = 2; i < CANT_THREADS; ++i)
        sem_post(&leer);
    lock.runlock();
    return nullptr;
}

void *lectores_t1(void*) {
    sem_wait(&leer);
    lock.rlock();
    // El escritor ya terminó
    assert(lock.writersLeft() == 0);
    lock.runlock();
    return nullptr;
}

void *escritor_t1(void*) {
    sem_wait(&escribir);
    lock.wlock();
    lock.wunlock();
    return nullptr;
}

// Test inanición 2 --------------------------------------------------------
// Queremos ver el orden en que llegan llamados del tipo:
// tanda de lectores - escritor - tanda de lectores
// ó tanda de escritores - lector - tanda de escritores
// Queremos ver que ni el escritor ni el lector quedan últimos siempre

void *lector(void*) {
    lock.rlock();
    std::cout << "R" << std::endl;
    usleep(50000);
    lock.runlock();
    return nullptr;
}

void *escritor(void*) {
    lock.wlock();
    std::cout << "W" << std::endl;
    usleep(50000);
    lock.wunlock();
    return nullptr;
}


// Test multithread --------------------------------------------------------
void *pTest(void* tidP) {
    int tid = (long) tidP;

    lock.rlock();

        assert(lock.isLocked());
        assert(lock.readersLeft() >= 1);
        cout << tid << " - Reading! "  << variable_global << endl;

    lock.runlock();

    lock.wlock();

        //assert(lock.isWriting());
        //assert(lock.writersLeft() >= 1);

        cout << tid << " - Writing! " << variable_global + 1 << endl;

        variable_global++;

        // Hago algo por 10 milisegundos
        usleep(10000);

        //variable_global--;

        //assert(not variable_global);

    lock.wunlock();

    return nullptr;
}


// Test básico -------------------------------------------------------------
void test_basic() {
    RWLockTester lock;

    assert(not lock.isLocked());

    lock.rlock();
    lock.rlock();
    lock.rlock();

    assert(lock.isLocked());
    assert(lock.readersLeft() == 3);

    lock.runlock();
    lock.runlock();
    lock.runlock();

    assert(not lock.isLocked());

    lock.wlock();

    assert(lock.isWriting());
    assert(lock.writersLeft() == 1);

    lock.wunlock();

    assert(not lock.isLocked());
}

int main() {

    // Test Basico

        test(test_basic);

        cout << "Test Basico Terminado!" << endl;

	// Test Multi Threads
    {
    	cout << "Empezamos Test Multi Threads! La variable_global vale: " << variable_global << endl;

        pthread_t thread[CANT_THREADS];
        int tid;

        for (tid = 0; tid < CANT_THREADS; ++tid)
             pthread_create(&thread[tid], NULL, pTest, (void*)(long)tid);

        for (tid = 0; tid < CANT_THREADS; ++tid)
             pthread_join(thread[tid], NULL);

        cout << "Terminamos Test Multi Threads! La variable_global vale: " << variable_global << endl;
    }

    // Test lecturas concurrentes (esperan a que estén todos los threads leyendo para soltar el lock)

    {
        cout << "Empezando test de lecturas concurrentes" << endl;

        pthread_t thread[CANT_THREADS];
        int tid;

        sem_init(&contador, 0, 0);

        for (tid = 0; tid < CANT_THREADS; ++tid)
             pthread_create(&thread[tid], NULL, lecturas_concurrentes, NULL);

        for (tid = 0; tid < CANT_THREADS; ++tid)
             pthread_join(thread[tid], NULL);


        cout << "Terminado test de lecturas concurrentes" << endl;
    }

    // Tests de inanición

        std::cout << "Empezando test de inanición (lectores a escritores) ---------------" << std::endl;
    {
        pthread_t thread[CANT_THREADS];
        int tid;

        sem_init(&leer, 0, 0);
        sem_init(&escribir, 0, 0);

        pthread_create(&thread[0], NULL, lector_t1, NULL);
        pthread_create(&thread[1], NULL, escritor_t1, NULL);

        // estos deberían esperar al escritor (ver funciones de cada thread)

        for (tid = 2; tid < CANT_THREADS; ++tid)
            pthread_create(&thread[tid], NULL, lectores_t1, NULL);

        for (tid = 0; tid < CANT_THREADS; ++tid)
             pthread_join(thread[tid], NULL);

        std::cout << "Terminado test de inanición (lectores a escritores)" << std::endl;
    }
    // Test de inanición en general, no assertea pero queremos ver el orden
    // en que ejecutan los llamados
    {
        std::cout << "Empezando test de inanición gral ---------------" << std::endl;

        pthread_t thread[CANT_THREADS];
        int tid;

        std::cout << "LECTORES -> ESCRITOR -> LECTORES" << std::endl;

            for (tid = 0; tid < CANT_THREADS/4; ++tid)
                pthread_create(&thread[tid], NULL, lector, NULL);

            pthread_create(&thread[CANT_THREADS/4], NULL, escritor, NULL);

            for (tid = CANT_THREADS/4 + 1; tid < CANT_THREADS/2; ++tid)
                pthread_create(&thread[tid], NULL, lector, NULL);

            for (tid = 0; tid < CANT_THREADS/2; ++tid)
                 pthread_join(thread[tid], NULL);
                 
        cout << endl << "ESCRITORES -> LECTOR -> ESCRITORES" << endl;

            for (tid = CANT_THREADS/2; tid < 3*CANT_THREADS/4; ++tid)
                pthread_create(&thread[tid], NULL, escritor, NULL);

            pthread_create(&thread[3*CANT_THREADS/4], NULL, lector, NULL);

            for (tid = 3*CANT_THREADS/4 + 1; tid < CANT_THREADS; ++tid)
                pthread_create(&thread[tid], NULL, escritor, NULL);

            for (tid = CANT_THREADS/2; tid < CANT_THREADS; ++tid)
                 pthread_join(thread[tid], NULL);

        std::cout << "Terminado test de inanición gral" << std::endl;
    }
    return 0;
}
