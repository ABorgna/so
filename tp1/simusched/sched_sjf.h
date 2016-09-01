#ifndef __SCHED_SJF__
#define __SCHED_SJF__

#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include "basesched.h"

using namespace std;

template<typename T>
using minheap = priority_queue<T, vector<T>, std::greater<T>>;

class SchedSJF : public SchedBase {
   public:
    SchedSJF(std::vector<int> argn);
    ~SchedSJF();
    virtual void initialize(){};
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

   private:
    /* llenar */
    minheap<pair<int, int>> espera;  //pid's en espera <tiempo, pid>
    map<int, int> tiempos;       //<pid, tiempo>
};

#endif
