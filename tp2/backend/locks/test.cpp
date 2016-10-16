#include "RWLock.h"

#include <cassert>
#include <iostream>

using namespace std;

#define  CANT_THREADS  5

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

void *pTest(void *p_lock) {
    RWLockTester lock = *((RWLockTester*) p_lock);
    assert(not lock.isLocked());

    lock.rlock();

    assert(lock.isLocked());
    assert(lock.readersLeft() == 1);
    cout << "Reading! "  << variable_global << endl;

    lock.runlock();

    assert(not lock.isLocked());

    lock.wlock();

    assert(lock.isWriting());
    assert(lock.writersLeft() == 1);
    variable_global++;
    variable_global--;
    cout << "Writing! " << variable_global << endl;

    lock.wunlock();

    assert(not lock.isLocked());

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

    cout << "done!" << endl;

	// Test Multi Threads

    RWLockTester lock;
	variable_global = 0;
	cout << "Empezamos! " << variable_global << endl;

    pthread_t thread[CANT_THREADS];
    int tid;

    for (tid = 0; tid < CANT_THREADS; ++tid) {
         pthread_create(&thread[tid], NULL, pTest, &lock);
    }

    for (tid = 0; tid < CANT_THREADS; ++tid)
         pthread_join(thread[tid], NULL);

    cout << "Terminamos! " << variable_global << endl;


    return 0;
}
