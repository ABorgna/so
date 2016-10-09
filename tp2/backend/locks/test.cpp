#include "RWLock.h"

#include <cassert>
#include <iostream>

using namespace std;

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
    test(test_basic);

    cout << "done!" << endl;

    return 0;
}
