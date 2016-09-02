#ifndef __SCHED_RSJF__
#define __SCHED_RSJF__

#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include "basesched.h"

using namespace std;

template<typename T>
using minheap = priority_queue<T, vector<T>, std::greater<T>>;

class SchedRSJF : public SchedBase {
   public:
    SchedRSJF(std::vector<int> argn);
    ~SchedRSJF();
    virtual void initialize(){};
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

   private:
    /* llenar */
    minheap<pair<int, int>> espera; //pid's en espera <tiempo, pid>
    map<int, int> tiempos;          //<pid, tiempo>

    vector<int> quantum_restante;  // deja vu
    vector<int> quantum_total;
};

#endif
