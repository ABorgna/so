#ifndef __SCHED_SJF__
#define __SCHED_SJF__

#include <algorithm>
#include <queue>
#include <vector>
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
};

#endif
