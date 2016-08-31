#ifndef __SCHED_MFQ__
#define __SCHED_MFQ__

#include <queue>
#include <vector>
#include "basesched.h"
#include <set>
#include <iostream>

using namespace std;

typedef std::vector<std::queue<int> > QueueArray;
typedef std::vector<std::set<int> > SetArray;

class SchedMFQ : public SchedBase {
   public:
    SchedMFQ(std::vector<int> argn);
    ~SchedMFQ();
    virtual void initialize(){};
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int n, const enum Motivo m);


   private:
    QueueArray colas;
    SetArray laUltimaColaVisitada;
	  std::vector<int> quantums;
    std::vector<int> quantumsRestantes;
};

#endif
