#include "RWLock.h"

#include <cassert>
#include <iostream>

#include <unistd.h>

using namespace std;

#define  CANT_THREADS  10

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


void *pTest(void*) {

    lock.rlock();

    assert(lock.isLocked());
    assert(lock.readersLeft() >= 1);
    cout << "Reading! "  << variable_global << endl;

    lock.runlock();

    lock.wlock();

    assert(lock.isWriting());
    assert(lock.writersLeft() >= 1);

    variable_global++;

    // Hago algo por 10 milisegundos
    sleep(0.01);

    variable_global--;

    assert(not variable_global);

    cout << "Writing! " << variable_global << endl;

    lock.wunlock();

    return NULL;

}

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

	cout << "Empezamos Test Multi Threads! La variable_global vale: " << variable_global << endl;

    pthread_t thread[CANT_THREADS];
    int tid;

    for (tid = 0; tid < CANT_THREADS; ++tid) {
         pthread_create(&thread[tid], NULL, pTest, NULL);
    }

    for (tid = 0; tid < CANT_THREADS; ++tid)
         pthread_join(thread[tid], NULL);

    cout << "Terminamos Test Multi Threads! La variable_global vale: " << variable_global << endl;


    return 0;
}
