#ifndef __SCHED_RSJF__
#define __SCHED_RSJF__

#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include "basesched.h"

using namespace std;

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
    set<pair<int, int>> espera;    //pid's en espera
    map<int, int> tiempos;         //<tiempo, pid>

    vector<int> quantum_restante;  // deja vu
    vector<int> quantum_total;
};

#endif
