#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include "basesched.h"

using namespace std;

class SchedRR : public SchedBase {
   public:
    SchedRR(std::vector<int> argn);
    ~SchedRR();
    virtual void initialize(){};
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

   private:
    std::queue<int> q;
    std::vector<int> quantum_total;    //Vector de cores con sus longitudes de quantums
    std::vector<int> quantum_restante; //Vector de cores con estado actual de quantums
};

#endif
