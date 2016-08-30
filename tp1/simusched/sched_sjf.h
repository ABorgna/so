#ifndef __SCHED_SJF__
#define __SCHED_SJF__

#include <algorithm>
#include <set>
#include <map>
#include "basesched.h"

using namespace std;

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
    set<pair<int, int>> espera;  //pid's en espera
    map<int, int> tiempos; //<tiempo, pid>
};

#endif
