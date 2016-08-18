#ifndef __SCHED_MFQ__
#define __SCHED_MFQ__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;
class SchedMFQ : public SchedBase {
	public:
		SchedMFQ(std::vector<int> argn);
        ~SchedMFQ();
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int n, const enum Motivo m);
	
	private:
/* llenar */
};

#endif
